struct producer { // ��������� �������������
	char city[64]; // ������ ������ (�������� - "Tver")
	char factory[64]; // ������ ������ (�������� - "Jabil Circuit")
	int release_year; // ��� ������� (�������� - 2009)
};

struct params { // ��������� ���������
	int price; // ���� (�������� - 255000) - � ������
	int screen_size; // ������ ������ (�������� - 65) - � ������
};

struct TV { // ��������� ��������� 
	char brand[64]; // ������ ����� (�������� - "Sony")
	struct producer Produser; // ��������� ��������� �������������
	struct params Params; // ��������� ��������� ���������
};
//  { "brand", { "city", "factory", release_year }, { price, screen_size } }