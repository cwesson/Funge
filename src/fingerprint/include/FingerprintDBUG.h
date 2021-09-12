/**
 * @file FingerprintDBUG.h
 * Software debugging.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include "FungeDebugger.h"

namespace Funge {

class FingerprintDBUG : public Fingerprint {
	public:
		FingerprintDBUG(FungeRunner& r);
		virtual ~FingerprintDBUG() = default;
		
		virtual bool execute(inst_t cmd) override;

		virtual void activate() override;
	
	private:
		FungeDebugger* dbg;
};

}
