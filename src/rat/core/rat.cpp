#include "rat.hpp"
#include "logger.hpp"

namespace rat {

	void printRat() {
		rat::log(R"(                                 _..----.._    _        )");
		rat::log(R"(                               ./  .--.    "-.(0)_      )");
		rat::log(R"(                     -.__-'"'=:|   ,  _)_ \__ .   '-..  )");
		rat::log(R"(                                '''------'---''---'-"   )");
		rat::log(R"(                                             $$$\       )");
		rat::log(R"(                        $$$\$$$\  $$$$$$$\  $$$$$$\     )");
		rat::log(R"(                        $$$$$$$$\ \    $$$\ \$$$  _|    )");
		rat::log(R"(                        $$$  -___|$$$$$$$$ | $$$ |      )");
		rat::log(R"(                        $$$ |    $$$   $$$ | $$$ |$$$\  )");
		rat::log(R"(                        $$$ |    \$$$$$$$$ | \$$$$$$  | )");
		rat::log(R"(                        \___|     \________|  \______/  )");
		rat::log("");
	}

} // namespace rat
