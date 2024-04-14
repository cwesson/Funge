/**
 * @file FingerprintTIME.h
 * Time and Date functions.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"

namespace Funge {

class FingerprintTIME : public Fingerprint {
	public:
		explicit FingerprintTIME(FungeRunner& r);
		virtual ~FingerprintTIME() = default;
		
		virtual FungeError execute(inst_t cmd) override;

	private:
		bool gmt;

		const std::tm* getTime();
};

}
