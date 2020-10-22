#include <utils_misc/int_macros.h>
#include <cli/mutex.hh>
#include <txtio/txtio_mutex.hh>
#include <mutex>

#define UOUT_PROTECTED
#include <uout/uo_callbacks.h>

uoCb_cbsT uoCb_cbs[cbs_size];
uoCb_Idxs uoCb_cbs_idxs;

uoCb_Idxs uoCb_filter(uo_flagsT flags, uoCb_Idxs idxs) {
  uoCb_Idxs result { };

  for (auto &it : uoCb_cbs) {
    if (it.cb) {
      continue;
    }
    if (0 == (it.flags.evt_flags & flags.evt_flags) && 0 == (it.flags.tgt_flags & flags.tgt_flags))
      continue;
    if (0 == (it.flags.fmt_flags & flags.fmt_flags))
      continue;

    result.arr[result.size++] = &it - &uoCb_cbs[0];
  }
  return result;
}

uoCb_Idxs uoCb_filter(uo_flagsT flags) {
  return uoCb_filter(flags, uoCb_cbs_idxs);
}

static void uoCb_update_idxs() {
  uoCb_cbs_idxs.size = 0;
  for (auto &it : uoCb_cbs) {
    uoCb_cbs_idxs.arr[uoCb_cbs_idxs.size++] = &it - &uoCb_cbs[0];
  }
}

bool uoCb_subscribe(uoCb_cbT msg_cb, uo_flagsT flags) {
  for (auto &it : uoCb_cbs) {
    if (it.cb) {
      continue;
    }
    it.cb = msg_cb;
    it.flags = flags;
    uoCb_update_idxs();
    return true;
  }
  return false;
}

bool uoCb_unsubscribe(uoCb_cbT msg_cb) {
  for (auto &it : uoCb_cbs) {
    if (it.cb != msg_cb)
      continue;
    it.cb = nullptr;
    it.flags.evt_flags = it.flags.fmt_flags = it.flags.tgt_flags = 0;
    uoCb_update_idxs();
    return true;
  }
  return false;
}

static void publish(uoCb_cbT cb, const void *ptr, uo_flagsT flags) {
  std::scoped_lock lock { cli_mutex, txtio_mutex };
  uoCb_msgT  msg { .cptr = ptr, .flags = flags };
  cb(msg);
}

void uoCb_publish_wsJson(const char *json) {
  for (auto const &it : uoCb_cbs) {
    if (!it.cb)
      continue;
    if (!it.flags.tgt.websocket)
      continue;

    uo_flagsT flags;
    flags.fmt.json = true;
    flags.tgt.websocket = true;

    publish(it.cb, json, flags);

  }
}

void uoCb_publish_pinChange(const so_arg_pch_t args) {
  for (auto const &it : uoCb_cbs) {
    if (!it.cb)
      continue;
    if (!it.flags.evt.pin_change)
      continue;

    if (it.flags.fmt.raw) {
      uo_flagsT flags;
      flags.fmt.raw = true;
      flags.evt.pin_change = true;

      publish(it.cb, &args, flags);
    }

    if (it.flags.fmt.json) {
      uo_flagsT flags;
      flags.fmt.json = true;
      flags.evt.pin_change = true;

      char buf[64];
      snprintf(buf, sizeof buf, "{\"mcu\":{\"gpio%d\":%d}}", args.gpio_num, args.level);
      publish(it.cb, buf, flags);
    }

  }
}

void uoCb_publish_ipAddress(const char *ip_addr) {
  for (auto const &it : uoCb_cbs) {
    if (!it.cb)
      continue;
    if (!it.flags.evt.ip_address_change)
      continue;

    if (it.flags.fmt.json) {
      uo_flagsT flags;
      flags.fmt.json = true;
      flags.evt.ip_address_change = true;

      char buf[64];
      snprintf(buf, sizeof buf, "{\"mcu\":{\"ipaddr\":\"%s\"}}", ip_addr);
      publish(it.cb, buf, flags);
    }

    if (it.flags.fmt.txt) {
      uo_flagsT flags;
      flags.fmt.txt = true;
      flags.evt.ip_address_change = true;

      char buf[64];
      snprintf(buf, sizeof buf, "tf: ipaddr: %s;\n", ip_addr);
      publish(it.cb, buf, flags);
    }
  }
}
