#include <atomic>
#include "ctagSoundProcessor.hpp"
#include "mifx/oliverb.h"

namespace CTAG {
    namespace SP {
        class ctagSoundProcessorMIVerb2 : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;

            virtual ~ctagSoundProcessorMIVerb2();

            ctagSoundProcessorMIVerb2();

            virtual const char *GetCStrID() const override;

        private:
            void setParamValueInternal(const string &id, const string &key, const int val) override;
            void loadPresetInternal() override;

// autogenerated code here
// sectionHpp
const string id = "MIVerb2";
void setIsStereo(){isStereo = true;}
atomic<int32_t> decay, cv_decay;
atomic<int32_t> amount, cv_amount;
atomic<int32_t> size, cv_size;
atomic<int32_t> in_gain, cv_in_gain;
atomic<int32_t> diffusion, cv_diffusion;
atomic<int32_t> lp, cv_lp;
atomic<int32_t> hp, cv_hp;
atomic<int32_t> mod_amount, cv_mod_amount;
atomic<int32_t> mod_rate, cv_mod_rate;
atomic<int32_t> ratio, cv_ratio;
atomic<int32_t> p_shift_amt, cv_p_shift_amt;
// sectionHpp



            // private attributes could go here
            mifx::Oliverb reverb;
            float *reverb_buffer;
        };
    }
}