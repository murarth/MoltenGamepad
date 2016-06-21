#include "redirect_trans.h"
#include "../event_translator_macros.h"

void redirect_trans::process(struct mg_ev ev, output_slot* out) {
  trans->process(ev, redirected);
  struct input_event out_ev;
  memset(&out_ev, 0, sizeof(out_ev));
  out_ev.type = EV_SYN;
  out_ev.code = SYN_REPORT;
  out_ev.value = 0;
  write_out(out_ev, redirected);

}

const MGType redirect_trans::fields[] = { MG_TRANS, MG_SLOT, MG_NULL };
redirect_trans::redirect_trans(std::vector<MGField>& fields) {
  BEGIN_READ_DEF;
  READ_TRANS(trans,MG_TRANS);
  READ_SLOT(redirected);
}
void redirect_trans::fill_def(MGTransDef& def) {
  BEGIN_FILL_DEF("redirect");
  FILL_DEF_TRANS(trans,MG_TRANS);
  FILL_DEF_SLOT(redirected);
}