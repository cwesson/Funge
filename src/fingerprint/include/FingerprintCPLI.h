/**
 * @file FingerprintCPLI.h
 * Complex integer extension.
 * @author Conlan Wesson
 */

#pragma once

#include "Fingerprint.h"
#include <complex>

namespace Funge {

class FingerprintCPLI : public Fingerprint {
	public:
		explicit FingerprintCPLI(FungeRunner& r);
		virtual ~FingerprintCPLI() = default;
		
		virtual FungeError execute(inst_t cmd) override;
	
	private:
		typedef std::complex<stack_t> cpli_t;
		typedef std::complex<double> cplf_t;
		cpli_t popComplex(Stack& stack);
		void pushComplex(Stack& stack, cpli_t comp);
		
		cplf_t toDouble(cpli_t comp);
		cpli_t toInt(cplf_t comp);
};

}
