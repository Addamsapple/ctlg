#include <fstream>

#include "command.h"

class Read : public Command {
	protected:
		std::ifstream _file;

		void _loadTypes();
		void _loadTitles();
		void _loadItems();
	public:
		virtual bool execute(StringVector arguments) override;
};
