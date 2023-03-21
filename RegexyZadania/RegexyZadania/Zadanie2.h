#pragma once
#include <string>
#include <vector>
#include <regex>

/*
Przychodzi do ciebie redaktor znanej gazety,

Cześć, potrzebuję twojej pomocy w napisaniu wyrażenia regularnego na adres email.
Chcę mieć narzędzie, które pozwoli mi na łatwe wyciąganie adresów email z różnych źródeł,
takich jak strony internetowe czy newslettery.

Czy mógłbyś napisać dla mnie wyrażenie regularne, które będzie wystarczająco skuteczne, 
aby wyłapać adresy email o różnych formatach, takich jak:
"nazwa@domena.com" czy też "nazwa@subdomena.domena.com"?
*/

struct Zadanie2 {

	void result() {
		std::regex reg("(\\w+)@((\\w+)\.\\w{2,3})|((\\w+)\.(\\w+)\.\\w{2,3})+");
		for (int i = 0; i < email_addresses.size(); i++) {
			std::cout << std::regex_match(email_addresses[i], reg);
		}

	}

	std::vector<std::string> email_addresses = {
		"shqtjm27kz@hotmail.com",
		"krazycaucazian@@otpku.com",
		"mattrkid@otpku.mailcuk.com",
		"yuliyabikb.ulato@timeroom.com",
		"filip.rudy@student.polsl.com",
	};
};
