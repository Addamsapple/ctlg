#include "command.h"

class Write : public Command {
	virtual bool execute(StringVector arguments) override;
};
