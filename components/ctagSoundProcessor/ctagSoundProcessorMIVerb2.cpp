#include "ctagSoundProcessorMIVerb2.hpp"
#include <iostream>
#include "clouds/dsp/frame.h"
#include "helpers/ctagFastMath.hpp"
#include "esp_log.h"
#include "esp_heap_caps.h"

using namespace CTAG::SP;

ctagSoundProcessorMIVerb2::ctagSoundProcessorMIVerb2() {
    setIsStereo();
    model = std::make_unique<ctagSPDataModel>(id, isStereo);
    model->LoadPreset(0);

    reverb_buffer = (float *) heap_caps_malloc(32768 * sizeof(float),
                                               MALLOC_CAP_SPIRAM);//MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (reverb_buffer == NULL) {
        ESP_LOGE("MIVerb", "Could not allocate shared buffer!");
    }

    reverb.Init(reverb_buffer);
}

void ctagSoundProcessorMIVerb2::Process(const ProcessData &data) {
    float fDecay = decay / 4095.f;
    if(cv_decay != -1){
        fDecay = HELPERS::fastfabs(data.cv[cv_decay]);
    }
    float fSize = size / 4095.f;
    if(cv_size != -1){
        fSize = HELPERS::fastfabs(data.cv[cv_size]);
    }
    float fGain = in_gain / 4095.f;
    if(cv_in_gain != -1){
        fGain = HELPERS::fastfabs(data.cv[cv_in_gain]);
    }
    float fDiffusion = diffusion / 4095.f;
    if(cv_diffusion != -1){
        fDiffusion = HELPERS::fastfabs(data.cv[cv_diffusion]);
    }
    float fLp = lp / 4095.f;
    if(cv_lp != -1){
        fLp = HELPERS::fastfabs(data.cv[cv_lp]);
    }
    float fHp = hp / 4095.f;
    if(cv_hp != -1){
        fHp = HELPERS::fastfabs(data.cv[cv_hp]);
    }
    float fModAmt = mod_amount / 4095.f;
    if(cv_mod_amount != -1){
        fModAmt = HELPERS::fastfabs(data.cv[cv_mod_amount]);
    }
    float fModRate = mod_rate / 4095.f;
    if(cv_mod_rate != -1){
        fModRate = HELPERS::fastfabs(data.cv[cv_mod_rate]);
    }
    float fRatio = ratio / 4095.f;
    if(cv_ratio != -1){
        fRatio = HELPERS::fastfabs(data.cv[cv_ratio]);
    }
    float fPShftAmt = p_shift_amt / 4095.f;
    if(cv_p_shift_amt != -1){
        fPShftAmt = HELPERS::fastfabs(data.cv[cv_p_shift_amt]);
    }
    float fAmount = amount / 4095.f;
    if(cv_amount != -1){
        fAmount = HELPERS::fastfabs(data.cv[cv_amount]);
    }

    reverb.set_decay(fDecay);
    reverb.set_ratio(fRatio);
    reverb.set_size(fSize);
    reverb.set_diffusion(fDiffusion);
    reverb.set_lp(fLp);
    reverb.set_input_gain(fGain);
    reverb.set_hp(fHp);
    reverb.set_mod_amount(fModAmt);
    reverb.set_mod_rate(fModRate);
    reverb.set_pitch_shift_amount(fPShftAmt);
    reverb.set_amount(fAmount);

    clouds::FloatFrame frames[bufSz];
    for(int i=0;i<bufSz;i++){
        frames[i].l = data.buf[i*2];
        frames[i].r = data.buf[i*2 + 1];
    }

    reverb.Process(frames, bufSz);

    for(int i=0;i<bufSz;i++){
        data.buf[i*2] = frames[i].l;
        data.buf[i*2 + 1] = frames[i].r;
    }

}

ctagSoundProcessorMIVerb2::~ctagSoundProcessorMIVerb2() {
    heap_caps_free(reverb_buffer);
}

const char *ctagSoundProcessorMIVerb2::GetCStrID() const {
    return id.c_str();
}


void ctagSoundProcessorMIVerb2::setParamValueInternal(const string& id, const string& key, const int val) {
// autogenerated code here
// sectionCpp0
if(id.compare("decay") == 0){
	if(key.compare("current") == 0){
		decay = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_decay = val;
	}
	return;
}
if(id.compare("amount") == 0){
	if(key.compare("current") == 0){
		amount = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_amount = val;
	}
	return;
}
if(id.compare("size") == 0){
	if(key.compare("current") == 0){
		size = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_size = val;
	}
	return;
}
if(id.compare("in_gain") == 0){
	if(key.compare("current") == 0){
		in_gain = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_in_gain = val;
	}
	return;
}
if(id.compare("diffusion") == 0){
	if(key.compare("current") == 0){
		diffusion = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_diffusion = val;
	}
	return;
}
if(id.compare("lp") == 0){
	if(key.compare("current") == 0){
		lp = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_lp = val;
	}
	return;
}
if(id.compare("hp") == 0){
	if(key.compare("current") == 0){
		hp = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_hp = val;
	}
	return;
}
if(id.compare("mod_amount") == 0){
	if(key.compare("current") == 0){
		mod_amount = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_mod_amount = val;
	}
	return;
}
if(id.compare("mod_rate") == 0){
	if(key.compare("current") == 0){
		mod_rate = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_mod_rate = val;
	}
	return;
}
if(id.compare("ratio") == 0){
	if(key.compare("current") == 0){
		ratio = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_ratio = val;
	}
	return;
}
if(id.compare("p_shift_amt") == 0){
	if(key.compare("current") == 0){
		p_shift_amt = val;
		return;
	}else if(key.compare("cv") == 0){
		if(val >= -1 && val <= 3)
			cv_p_shift_amt = val;
	}
	return;
}
// sectionCpp0


}

void ctagSoundProcessorMIVerb2::loadPresetInternal() {
// autogenerated code here
// sectionCpp1
decay = model->GetParamValue("decay", "current");
cv_decay = model->GetParamValue("decay", "cv");
amount = model->GetParamValue("amount", "current");
cv_amount = model->GetParamValue("amount", "cv");
size = model->GetParamValue("size", "current");
cv_size = model->GetParamValue("size", "cv");
in_gain = model->GetParamValue("in_gain", "current");
cv_in_gain = model->GetParamValue("in_gain", "cv");
diffusion = model->GetParamValue("diffusion", "current");
cv_diffusion = model->GetParamValue("diffusion", "cv");
lp = model->GetParamValue("lp", "current");
cv_lp = model->GetParamValue("lp", "cv");
hp = model->GetParamValue("hp", "current");
cv_hp = model->GetParamValue("hp", "cv");
mod_amount = model->GetParamValue("mod_amount", "current");
cv_mod_amount = model->GetParamValue("mod_amount", "cv");
mod_rate = model->GetParamValue("mod_rate", "current");
cv_mod_rate = model->GetParamValue("mod_rate", "cv");
ratio = model->GetParamValue("ratio", "current");
cv_ratio = model->GetParamValue("ratio", "cv");
p_shift_amt = model->GetParamValue("p_shift_amt", "current");
cv_p_shift_amt = model->GetParamValue("p_shift_amt", "cv");
// sectionCpp1


}
