/*
 * I2C_driver.c
 *
 *  Created on: Dec 12, 2025
 *      Author: Karol
 */
#include "I2C_driver.h"

/*
 *
 * ARGS:
	 * Tx_frame - struktura z informacją o ramce głównej
	 * Pre_post_send - struktura z ramkami do wysyłki po i przed ramką główną
 * RETURN:
 	 * HAL_OK - pomyślnie wykonano operacje
 	 * HAL_ERROR - wystąpił błąd -> wywołąnie asser_failed()
 *
 */
HAL_StatusTypeDef I2C_Transmit_message(I2C_frame* Tx_frame, I2C_pre_post_frame* Pre_post_send) // Funkcja do wysyłki danych po I2C

{

	if (Tx_frame->addres <= 0x7F)							// Adres wraz z bitem Write/Read ma dokładnie 8 bitów
	{
		assert_failed(__FILE__, __LINE__);
	}

	for (uint8_t i = 0; i < Pre_post_send->size_pre; i++)	// Informacja przed ramką główną
	{
		HAL_I2C_Master_Transmit(CURRENT_PRE(i).hi2c, CURRENT_PRE(i).addres, NULL, 0, CURRENT_PRE(i).timeout);
		HAL_Delay(CURRENT_PRE(i).delay);						//OPCJONALNY ALE DLA AM2320 MUSI BYC
	}

	if (HAL_I2C_Master_Transmit(Tx_frame->hi2c, Tx_frame->addres, Tx_frame->data , Tx_frame->size_data, Tx_frame->timeout) != HAL_OK )
	{
		assert_failed(__FILE__, __LINE__);					// Ramka główna
	}

	for (uint8_t i = 0; i < Pre_post_send->size_post; i++)	// Informacja po ramce głównej
	{
		HAL_Delay(CURRENT_POST(i).delay);					//OPCJONALNY ALE DLA AM2320 MUSI BYC
		HAL_I2C_Master_Transmit(CURRENT_POST(i).hi2c, CURRENT_POST(i).addres, CURRENT_POST(i).data, CURRENT_POST(i).size_data, CURRENT_POST(i).timeout);
	}


	return HAL_OK;
}


// FUNKCJA MA BYĆ UŻYTA W TIMER KTÓRY BĘDZIE WYWOŁYWANY CO OKRES MIEDZY RAMKAMKI NP. DLA AM2320 TO 1MS.
/*
 *
 * ARGS:
	 * Rx_frame - struktura z informacją o ramce głównej
	 * Pre_post_send - struktura z ramkami do wysyłki po i przed ramką główną
 * RETURN:
 	 * HAL_OK - pomyślnie wykonano operacje
 	 * HAL_ERROR - wystąpił błąd -> wywołąnie asser_failed()
 *
 */
HAL_StatusTypeDef I2C_Receive_message(I2C_frame* Rx_frame, I2C_pre_post_frame* Pre_post_send)

{
	static int8_t i = -1; // wykonuje się tylko raz !
	i++;

	//HAL_Delay(Rx_frame->delay);

	if (Rx_frame->addres <= 0x7F && i == 0)// adres wraz z bitem Write/Read ma dokładnie 8 bitów
	{
		assert_failed(__FILE__, __LINE__);
	}

	while (i < Pre_post_send->size_pre)		// Informacja przed ramą główną
	{
		HAL_I2C_Master_Transmit(CURRENT_PRE(i).hi2c, CURRENT_PRE(i).addres, NULL, 0, CURRENT_PRE(i).timeout);
		return HAL_OK;
		//HAL_Delay(CURRENT_PRE(i).delay);						//OPCJONALNY ALE DLA AM2320 MUSI BYC
	}

	if (i == Pre_post_send->size_pre && HAL_I2C_Master_Receive(Rx_frame->hi2c, Rx_frame->addres, Rx_frame->data, Rx_frame->size_data, Rx_frame->timeout) != HAL_OK )
	{
		assert_failed(__FILE__, __LINE__);
		return HAL_ERROR;										// Ramka główna
	}
	else
	{
		return HAL_OK;
	}


	while (Pre_post_send->size_pre < i  && i <= (Pre_post_send->size_post + Pre_post_send->size_pre))		// Informacja po ramce głównej
	{
		HAL_I2C_Master_Transmit(CURRENT_POST(i).hi2c, CURRENT_POST(i).addres, CURRENT_POST(i).data, CURRENT_POST(i).size_data, CURRENT_POST(i).timeout);
		return HAL_OK;
		//HAL_Delay(CURRENT_POST(i).delay);						//OPCJONALNY ALE DLA AM2320 MUSI BYC
	}

	i = -1;
	return HAL_OK;
}

// FUNCKJA SPRAWDZAJĄCA CZY ADRESY RAMEK SĄ W ZAKRESIE <128, 255>
/*
 *
 * ARGS:
	 * Frames - Tablica struktur z ramkami
 * RETURN:
 	 * HAL_OK - Ramki nie zawierają błędów
 	 * HAL_ERROR - Ramki zawierają błąd
 *
 */
HAL_StatusTypeDef I2C_Valid_address(I2C_frame* Frames, uint8_t Size)
{
	uint8_t bit_map[16] = {0}; // 16*8 = 128
	uint8_t byte = 0;
	uint8_t bit = 0;
	int16_t address = 0;

	for(uint8_t i = 0; i < Size; i++){
		address = Frames[i].addres - 128; // przesuwam adres do zakresu <0,127>

		byte = address / 8;		// sprawdzam na którym ideksie czyli bajcie w tablicy bit_map wylonduje adres
		bit  = address % 8;		// określa na którym miejscu w ciągu 00000000 jest jedynka.

		if ( address < 0 || byte >= 16|| bit_map[byte] & (1 << bit)) { 	// jeśli wartość adresu z struktury była mniejsza niż 128 to wyłapie to address<0
																		// jeśli wartość adresu z struktury ponad 255
																		// sprawdzam czy w bit_map nie ma już takiej liczby
			return HAL_ERROR;		// ADRESY SIĘ POWAŻAJĄ
		}

		bit_map[byte] |= (1 << bit);									// zapisuje w bit map liczbę wynikową z operacji: map_bit[byte] OR np.(00010000) miejsce jedynki zależne od zmiennej bit,
	}
	return HAL_OK; // adresy POPRAWNE
}
