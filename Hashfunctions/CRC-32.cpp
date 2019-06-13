#define uint unsigned int
/*
    Name  : CRC-32
    Poly  : 0x04C11DB7    x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11
					   + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
    Init  : 0xFFFFFFFF
    Revert: true
    XorOut: 0xFFFFFFFF
    Check : 0xCBF43926 ("123456789")
    MaxLen: 268 435 455 байт (2 147 483 647 бит) - обнаружение
    одинарных, двойных, пакетных и всех нечетных ошибок
    buf - кол-во бит в файле
    len - кол-во символов в файле
*/

uint CRC32_function(unsigned char *buf, unsigned long len)
{
	unsigned long crc_table[256];
	unsigned long crc;
	for (int i = 0; i < 256; i++)
	{
		crc = i;
		for (int j = 0; j < 8; j++)
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
		crc_table[i] = crc;
	};
	crc = 0xFFFFFFFFUL;
	while (len--)
		crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
	return crc ^ 0xFFFFFFFFUL;
}