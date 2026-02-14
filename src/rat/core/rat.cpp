#include "rat.hpp"
#include "logger.hpp"

namespace rat {

	void printRat() {
		rat::info(R"(                                 _..----.._    _        )");
		rat::info(R"(                               ./  .--.    "-.(0)_      )");
		rat::info(R"(                     -.__-'"'=:|   ,  _)_ \__ .   '-..  )");
		rat::info(R"(                                '''------'---''---'-"   )");
		rat::info(R"(                                             $$$\       )");
		rat::info(R"(                        $$$\$$$\  $$$$$$$\  $$$$$$\     )");
		rat::info(R"(                        $$$$$$$$\ \    $$$\ \$$$  _|    )");
		rat::info(R"(                        $$$  -___|$$$$$$$$ | $$$ |      )");
		rat::info(R"(                        $$$ |    $$$   $$$ | $$$ |$$$\  )");
		rat::info(R"(                        $$$ |    \$$$$$$$$ | \$$$$$$  | )");
		rat::info(R"(                        \___|     \________|  \______/  )");
		rat::info("");
	}

} // namespace rat
