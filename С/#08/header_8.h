struct producer { // структура Производитель
	char city[64]; // строка Города (Например - "Tver")
	char factory[64]; // строка Завода (Например - "Jabil Circuit")
	int release_year; // Год выпуска (Например - 2009)
};

struct params { // структура Параметры
	int price; // Цена (Например - 255000) - в рублях
	int screen_size; // Размер экрана (Например - 65) - в дюймах
};

struct TV { // структура Телевизор 
	char brand[64]; // строка Марки (Например - "Sony")
	struct producer Produser; // экземпляр структуры Производитель
	struct params Params; // экземпляр структуры Параметры
};
//  { "brand", { "city", "factory", release_year }, { price, screen_size } }