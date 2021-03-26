#include <random>
#include <iostream>
#include <chrono>
#include <sstream>

int read_int (const char *question) {
	int result;
	std::string inp;
	re: std::cout << question;
	std::getline (std::cin, inp); {
		std::stringstream inps {inp};
		inps >> result;
		if (inps.fail()){
			if (std::cin.fail()){
				std::cerr <<"Ошибка ввода-вывода!" << std::endl;
				exit(1);
				}
			std::cout << "Некорректный ввод!" << std::endl;
			goto re;
		}
		else if (not inps.eof()){
			std::cout << "Непонятный мусор в конце ввода!" << std::endl;
			goto re;
		}
	}
	return result;
}

int read_int_in_range(const char * question, int min, int max) {
	int result;
	for(;;) {
		result = read_int(question);
		if (result >= min and result <= max) return result;
		std::cout << "Число должно быть в интервале от "
				<< min << " до " << max << std::endl;
		}
	}

int main(){

	using clk = std::chrono::system_clock;
	std::random_device rd;
	std::minstd_rand rnd{unsigned(clk::now().time_since_epoch().count())};
	std::uniform_int_distribution<> d {15,25};
	std::uniform_int_distribution <> d1{1,3};

	int Level;

	//Цикл
	do {
	unsigned PlayerStone = d(rnd);
	Level = read_int_in_range("Set the game's difficulty:\n"
							"1) Easy\n"
							"2) Medium\n"
							"3) You shall not pass\n"
							"4) Exit (are you sure?)\n", 1, 4);

	if (Level==4)	return 0;
	std::cout << "Количество камней в куче: " << PlayerStone << ";" << std::endl;

	while (Level!=4) {
		std::cout << "Возьмите 1/2/3 камня из кучи!" << std::endl;
		std::cout << "Проигрывает тот, кто забирает последний камень." << std::endl;
		std::cout << std::endl;
		std::cout << "Ваше количество:" << std::endl;
		int x = read_int_in_range("", 1, std::min (3U, PlayerStone));
		PlayerStone = PlayerStone - x;

		if (PlayerStone < 26) std::cout << "Количество камней в куче: " << PlayerStone << ";" << std::endl;
		if (PlayerStone == 0 || PlayerStone > 25) { std::cout << "Game Over!\n" << std::endl; break; }
		else {
			unsigned IIStone;
			if (PlayerStone < 5 && Level != 1){
				// Если не легкая сложность
					switch(PlayerStone){
						case 4: IIStone = 3; break;
						case 3: IIStone = 2; break;
						case 2: IIStone = 1; break;
					}
			} else {
				if(Level == 1) IIStone = d1(rnd); // Первый уровень
				else if (Level == 2){ // Второй
					switch(x){
						case 1: IIStone = 3; break;
						case 2: IIStone = 2; break;
						case 3: IIStone = 1; break; }

				} else { // Третий
					for(unsigned i = 25; i > 0; i -= 4){
						if (i == PlayerStone){ IIStone = d1(rnd); break;}
						if (PlayerStone > i){ IIStone = PlayerStone - i; break;}
					}
				}
			}

		PlayerStone = PlayerStone - IIStone;
		std::cout << "ИИ взял " << IIStone << " камней" << std::endl;

		if (PlayerStone == 0 || PlayerStone > 25) {std::cout << "Victory!\n" << std::endl; break;}
		std::cout << "Количество камней в куче: " << PlayerStone << ";" << std::endl;

		}
	}
	} while (1==1);

return 0;
}









