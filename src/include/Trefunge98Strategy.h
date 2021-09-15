/**
 * @file Trefunge98Strategy.h
 * Strategy for Trefunge-98 commands.
 * @author Conlan Wesson
 */

#pragma once

#include "FungeStrategy.h"

namespace Funge {

class Trefunge98Strategy : public FungeStrategy {
	public:
		Trefunge98Strategy(FungeRunner& r);
		virtual ~Trefunge98Strategy() = default;
		
		virtual bool execute(inst_t cmd) override;
		virtual FungeStrategy* clone(FungeRunner& r) const override;
};

}
