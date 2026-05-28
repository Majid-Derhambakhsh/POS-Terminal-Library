/*
------------------------------------------------------------------------------
~ File   : pos_terminal.c
~ Author : Majid Derhambakhsh
~ Version: V1.0.0
~ Created: 01/10/2024 03:00:00 PM
~ Brief  :
~ Support: 
           E-Mail : Majid.Derhambakhsh@Outlook.com (subject : Embedded Library Support)
		   
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    

~ Changes    :
------------------------------------------------------------------------------
*/

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "pos_terminal.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ G Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ G Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ G Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int32_t Pow(int32_t i, int32_t k)
{
	
	int32_t j = 1;

	while (k > 0)
	{
		j *= i;
		k--;
	}

	return j;
	
}

/* .......................... Buffer ........................... */
void POS_UART_ClearBuffer(POS_TypeDef *POS)
{
	
	if (POS->RxCounter > 0)
	{
		
		/* ~~~~~ Clear UART received data ~~~~ */
		memset(POS->RxBuffer, '\0', POS->RxCounter);
		
		/* ~~~~~ Reset UART data counter ~~~~~ */
		POS->RxCounter = 0;
		
	}
	
}

/* ...................... Type Conversion ...................... */
/*
 * Function: POS_BinToDec
 * ----------------------
 * The POS_BinToDec function converts an array of binary digits to a decimal number.
 *
 * Param  : 
 *         Arr: A pointer to an array of binary digits.
 *         Length: The length of the array.
 *         
 * Returns: 
 *         The decimal number equivalent to the input array.
 *         
 * Example: 
 *         bool Arr[] = {1, 0, 1, 1};
 *         
 *         uint8_t DecimalValue = POS_BinToDec(Arr, 4);
 *         
 *         printf("Decimal value: %d\n", DecimalValue);
 *         
 * Output :
 *         Decimal value: 11
 */
uint8_t POS_BinToDec(bool *Arr, uint8_t Length)
{
    uint8_t Result = 0;
	
	/* ------------- Convert binary to Decimal -------------- */
    for (uint8_t i = 0; i < Length; i++)
	{
        Result |= Arr[i] << (Length - 1 - i);
    }
	
    return Result;
	
}

/* ............................................................. */
/*
 * Function: POS_CopyFirstBytes
 * ----------------------------
 * The POS_CopyFirstBytes function copies a specified number of bytes from the beginning of one array to another.
 *
 * Param  : 
 *         Out: A pointer to the destination array where the bytes will be copied.
 *         Src: A pointer to the source array where the bytes are copied from.
 *         CopySize: The number of bytes to copy.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool Out[10];
 *         bool Src[10] = {1, 0, 1, 1, 0, 0, 1, 1, 0, 0};

 *         POS_CopyFirstBytes(Out, Src, 4);
 *         
 *         // The first 4 bytes of Out will be: {1, 0, 1, 1}
 *         
 */
void POS_CopyFirstBytes(bool *Out, bool *Src, uint16_t CopySize)
{
	memcpy(Out, Src, CopySize);
}

/*
 * Function: POS_CopyLastBytes
 * ---------------------------
 * The POS_CopyLastBytes function copies a specified number of bytes from the end of one array to another.
 *
 * Param  : 
 *         Out: A pointer to the destination array where the bytes will be copied.
 *         Src: A pointer to the source array where the bytes are copied from.
 *         CopySize: The number of bytes to copy.
 *         ArrLength: The length of the source array.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool Out[10];
 *         bool Src[10] = {1, 0, 1, 1, 0, 0, 1, 1, 0, 0};

 *         POS_CopyLastBytes(Out, Src, 4, 10);
 *         
 *         // The last 4 bytes of Out will be: {1, 1, 0, 0}
 *         
 */
void POS_CopyLastBytes(bool *Out, bool *Src, uint16_t CopySize, uint16_t ArrLength)
{
	memcpy(Out, Src + ArrLength - CopySize, CopySize);
}

/*
 * Function: POS_AppendDecimalToArray
 * ----------------------------------
 * The POS_AppendDecimalToArray function appends a decimal value to the end of an array of bytes. It also updates an index variable to point to the next available byte in the array.
 *
 * Param  : 
 *         Arr: A pointer to the array where the decimal value will be appended.
 *         Indx: A pointer to an index variable that points to the next available byte in the array. After the function is called, this variable will be updated to point to the byte after the appended value.
 *         Dec: The decimal value to be appended to the array.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         uint8_t Buffer[10];
 *         uint16_t Index = 0;
 *         
 *         uint32_t DecimalValue = 1598;
 *         
 *         POS_AppendDecimalToArray(Buffer, &Index, DecimalValue);
 *         
 *         // The first 2 bytes of Buffer will be: {0x06, 0x3E}
 *         
 */
void POS_AppendDecimalToArray(uint8_t *Arr, uint16_t *Indx, uint32_t Dec)
{
	uint16_t index = *Indx;
	
	/* ---------------- Append Decimal Value ---------------- */
	if (Dec > 0xFFFFFF)
	{
		Arr[index++] = (uint8_t)(Dec >> 24);
	}
	
	if (Dec > 0xFFFF)
	{
		Arr[index++] = (uint8_t)(Dec >> 16);
	}
	
	if (Dec > 0xFF)
	{
		Arr[index++] = (uint8_t)(Dec >> 8);
	}
	
	Arr[index++] = (uint8_t)Dec;
	
	/* -------------------- Update Index -------------------- */
	*Indx = index;
	
}

/*
 * Function: POS_XORBits
 * ---------------------
 * The POS_XORBits function performs a bitwise XOR operation on two arrays of boolean values and stores the result in a third array.
 *
 * Param  : 
 *         Out: A pointer to the output array where the XOR result will be stored. This array must have the same length as BitArr1 and BitArr2.
 *         BitArr1: A pointer to the first input array of boolean values.
 *         BitArr2: A pointer to the second input array of boolean values.
 *         Length: The length of the input arrays.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool Out[8];
 *         bool BitArr1[8] = {1, 0, 1, 1, 0, 0, 1, 1};
 *         bool BitArr2[8] = {0, 1, 0, 0, 1, 1, 0, 1};
 *         
 *         POS_XORBits(Out, BitArr1, BitArr2, 8);
 *         
 *         // The content of Out will be: {1, 1, 1, 1, 1, 1, 1, 0}
 *         
 */
void POS_XORBits(bool *Out, bool *BitArr1, bool *BitArr2, uint8_t Length)
{
	/* ------------ XOR Loop for Large Than 4-bit ----------- */
	for (uint8_t Ic = 0; Ic < Length; Ic += 4)
	{
		Out[Ic] = BitArr1[Ic] ^ BitArr2[Ic];
		Out[Ic + 1] = BitArr1[Ic + 1] ^ BitArr2[Ic + 1];
		Out[Ic + 2] = BitArr1[Ic + 2] ^ BitArr2[Ic + 2];
		Out[Ic + 3] = BitArr1[Ic + 3] ^ BitArr2[Ic + 3];
	}
	
	/* ------------ XOR Loop for Small Than 4-bit ----------- */
	for (uint8_t Ic = Length & ~3; Ic < Length; Ic++)
	{
		Out[Ic] = BitArr1[Ic] != BitArr2[Ic];
	}
	
}

/* ......................... DES - Key ......................... */
/*
 * Function: POS_DES_KeyPermutation
 * --------------------------------
 * The POS_DES_KeyPermutation function performs the key permutation step of the DES algorithm.
 *
 * Param  : 
 *         KeyPlus: A pointer to the array where the permuted key will be stored.
 *         Key: A pointer to the array containing the original key.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool KeyPlus[56];
 *         bool Key[64] = { ... }; // 64-bit key
 *         
 *         POS_DES_KeyPermutation(KeyPlus, Key);
 *         
 *         // The permuted key will be stored in the KeyPlus array.
 *         
 */
void POS_DES_KeyPermutation(bool *KeyPlus, bool *Key)
{
	/* ---- Permutation Choice 1 Table for DES Algorithm ---- */
	uint8_t permutationChoice1[56] =
	{
		57, 49, 41, 33, 25, 17, 9 , 1,
		58, 50, 42, 34, 26, 18, 10, 2,
		59, 51, 43, 35, 27, 19, 11, 3,
		60, 52, 44, 36, 63, 55, 47, 39,
		31, 23, 15, 7 , 62, 54, 46, 38,
		30, 22, 14, 6 , 61, 53, 45, 37,
		29, 21, 13, 5 , 28, 20, 12, 4
	};
	
	/* ---------------- Move Bits to New Key ---------------- */
	for (uint8_t i = 0; i < 56; i++)
	{
		KeyPlus[i] = Key[permutationChoice1[i] - 1];
	}
	
}

/* ....................... DES - Sub Key ....................... */
/*
 * Function: POS_DES_SubKeyShift
 * -----------------------------
 * The The POS_DES_SubKeyShift function shifts the bits of the subkey in the DES algorithm.
 *
 * Param  : 
 *         SubKey: A pointer to the subkey array.
 *         KeyFlag: A flag that indicates whether the key is being shifted for encryption or decryption.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool SubKey[28] = { ... };
 *         bool KeyFlag = true;
 *         
 *         POS_DES_SubKeyShift(SubKey, KeyFlag);
 *         
 *         // The subkey bits have been shifted.
 *         
 */
void POS_DES_SubKeyShift(bool *SubKey, bool KeyFlag)
{
	bool subKey0 = SubKey[0];
	
	/* --------------------- Shift Keys --------------------- */
	if (KeyFlag)
	{
		for (uint8_t i = 1 ; i < 28; i++)
		{
			SubKey[i-1] = SubKey[i];
		}
		
		SubKey[27] = subKey0;
		
	}
	else
	{
		bool subKey1 = SubKey[1];
		
		for (uint8_t i = 2 ; i < 28; i++)
		{
			SubKey[i-2] = SubKey[i];
		}
		
		SubKey[26] = subKey0;
		SubKey[27] = subKey1;
		
	}
	
}

/*
 * Function: POS_DES_SubKeyGenerator
 * ---------------------------------
 * The POS_DES_SubKeyGenerator function generates the subkeys for the DES algorithm.
 *
 * Param  : 
 *         Out: A pointer to the output array where the subkey will be stored.
 *         Cin: A pointer to the first half of the input key.
 *         Din: A pointer to the second half of the input key.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool Out[48];
 *         bool Cin[28] = { ... };
 *         bool Din[28] = { ... };
 *         
 *         POS_DES_SubKeyGenerator(Out, Cin, Din);
 *         
 *         // The subkey has been generated in the Out array.
 *         
 */
void POS_DES_SubKeyGenerator(bool *Out, bool *Cin, bool *Din)
{
	
	bool keyTable[56];
	
	/* ---- Permutation Choice 2 Table for DES Algorithm ---- */
	uint8_t permutationChoice2[48] =
	{
		14, 17, 11, 24, 1 , 5 , 3 , 28,
		15, 6 , 21, 10, 23, 19, 12, 4 ,
		26, 8 , 16, 7 , 27, 20, 13, 2 ,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32
	};
	
	/* ------------------ Generate Sub Key ------------------ */
	for (uint8_t i = 0; i < 28; i++)
	{
		keyTable[i] = Cin[i];
		keyTable[i + 28] = Din[i];
	}
	
	for (uint8_t i = 0; i < 48; i++)
	{
		Out[i] = keyTable[permutationChoice2[i] - 1];
	}
	
}

/* ..................... DES - Processing ...................... */
/*
 * Function: POS_DES_IPMaker
 * -------------------------
 * The POS_DES_IPMaker function performs the initial permutation (IP) on the input data in the DES algorithm.
 *
 * Param  : 
 *         Out: A pointer to the output array where the IP result will be stored.
 *         MEntry: A pointer to the input array containing the data to be permuted.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool Out[64];
 *         bool MEntry[64] = { ... };
 *         
 *         POS_DES_IPMaker(Out, MEntry);
 *         
 *         // The output array `Out` will contain the permuted data.
 *         
 */
void POS_DES_IPMaker(bool *Out, bool *MEntry)
{
	/* ----- Initial Permutation Table for DES Algorithm ---- */
	uint8_t initialPermutation[64] =
	{
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9 , 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7
	};
	
	/* --------------------- Generate IP -------------------- */
	for (uint8_t i = 0; i < 64 ; i++)
	{
		Out[i] = MEntry[initialPermutation[i] - 1];
	}
	
}

/*
 * Function: POS_DES_ExpansionPermutation
 * --------------------------------------
 * The POS_DES_ExpansionPermutation function performs the expansion permutation in the DES algorithm.
 *
 * Param  : 
 *         Out: A pointer to the output array where the expanded bits will be stored.
 *         Bin: A pointer to the input array of 32 bits.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool Out[32];
 *         bool Bin[32] = { ... };
 *         
 *         POS_DES_ExpansionPermutation(Out, Bin);
 *         
 *         // The output array `Out` will contain the expanded bits.
 *         
 */
void POS_DES_ExpansionPermutation(bool *Out, bool *Bin)
{
	/* - Expansion Permutation Box 1 Table for DES Algorithm - */
	uint8_t expansionPermutationBox1[32] =
	{
		16, 7 , 20, 21, 29, 12, 28, 17,
		1 , 15, 23, 26, 5 , 18, 31, 10,
		2 , 8 , 24, 14, 32, 27, 3 , 9 ,
		19, 13, 30, 6 , 22, 11, 4 , 25
	};
	
	/* ----------- Generate Expansion Permutation ------------ */
	for (uint8_t i = 0; i < 32 ; i++)
	{
		Out[i] = Bin[expansionPermutationBox1[i] - 1];
	}
	
}

/*
 * Function: POS_DES_SBoxTransformation
 * ------------------------------------
 * The POS_DES_SBoxTransformation function performs the S-box transformation for the Data Encryption Standard (DES) algorithm.
 *
 * Param  : 
 *         Out: A pointer to a 32-bit array that will store the output data (4 bits per S-box).
 *         BiS: A pointer to a 48-bit array containing the input data (6 bits per S-box).
 *         
 * Returns: 
 *         -
 *         
 */
void POS_DES_SBoxTransformation(bool *Out, bool *BiS)
{
	/* ----------------- Define the S-boxes ----------------- */
	uint8_t SBox[8][4][16] =
	{
		{
			{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
			{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
			{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
			{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
		},
		{
			{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
			{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
			{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
			{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
		},
		{
			{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
			{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
			{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
			{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
		},
		{
			{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
			{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
			{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
			{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
		},
		{
			{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
			{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
			{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
			{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
		},
		{
			{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
			{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
			{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
			{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
		},
		{
			{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
			{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
			{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
			{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
		},
		{
			{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
			{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
			{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
			{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
		}
	};	
	
	/* ----------- Iterate over the eight S-boxes ----------- */
	uint8_t counter = 0;
	
	for (uint8_t i = 0; i < 8; i++)
	{
		/* ~~~~ Extract the input bits for the current S-box ~~~~ */
		bool Bs[6];
		
		for (uint8_t j = 0; j < 6; j++)
		{
			Bs[j] = BiS[i * 6 + j];
		}
		
		/* ~~~~ Divide the input bits into row and column ~~~~~~~
		   ~~~~~~~~~~~~~~~ indices for the S-box ~~~~~~~~~~~~~~~~ */
		bool bx[2] = {Bs[0], Bs[5]};
		bool by[4] = {Bs[1], Bs[2], Bs[3], Bs[4]};
		
		uint8_t X = POS_BinToDec(bx, 2);
		uint8_t Y = POS_BinToDec(by, 4);
		
		/* ~~~~~~~~ Look up the S-box value based on the ~~~~~~~~
		   ~~~~~~~~~~~~~~~ row and column indices ~~~~~~~~~~~~~~~ */
		uint8_t SBoxValue = SBox[i][X][Y];
		
		/* ~~~~ Extract the output bits from the S-box value ~~~~ */
		for (int32_t k = 0; k < 4; k++)
		{
			
			int32_t p = Pow(2, 3 - k);
			
			Out[counter] = ((int32_t) (SBoxValue / p) != 0), counter++;
			SBoxValue = SBoxValue % p;
			
		}
		
	}
	
}

/*
 * Function: POS_DES_ExpandBits
 * ----------------------------
 * The POS_DES_ExpandBits function expands 32-bit input data to 48 bits using a specific order based on the DES (Data Encryption Standard) algorithm.
 *
 * Param  : 
 *         Out: Pointer to a 48-bit output array where the expanded bits will be stored.
 *         InputBits: Pointer to a 32-bit input array containing the data to be expanded.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool InputBits[32] = { ... }; // Your 32-bit input data
 *         bool Out[48]; // Empty array to store the expanded output
 *         
 *         POS_DES_ExpandBits(Out, InputBits);
 *         
 *         // Now the `Out` array contains the expanded 48 bits
 *         
 */
void POS_DES_ExpandBits(bool *Out, bool *InputBits)
{
	/* -------- Expand Bit Indices for DES Algorithm -------- */
	uint8_t expandBitIndices[48] =
	{
		32, 1 , 2 , 3 , 4 , 5 , 4 , 5 ,
		6 , 7 , 8 , 9 , 8 , 9 , 10, 11,
		12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21,
		22, 23, 24, 25, 24, 25, 26, 27,
		28, 29, 28, 29, 30, 31, 32, 1
	};
	
	/* ------------------ Expand Input Bits ----------------- */
	for (uint8_t i = 0 ; i < 48; i++)
	{
		Out[i] = InputBits[expandBitIndices[i] - 1];
	}
	
}

/*
 * Function: POS_DES_IP1
 * ---------------------
 * The POS_DES_IP1 function applies the initial permutation (IP-1) to the input data in the DES algorithm.
 *
 * Param  : 
 *         Result: A pointer to the array where the result will be stored.
 *         RLin: A pointer to the array containing the input data.
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         bool Result[64];
 *         bool RLin[64] = { ... };
 *         
 *         POS_DES_IP1(Result, RLin);
 *         
 *         // The result array now contains the IP-1 of the input data.
 *         
 */
void POS_DES_IP1(bool *Result, bool *RLin)
{
	/* ----- Initial Permutation Table for DES Algorithm ---- */
	uint8_t initialPermutation1[64] =
	{
		40, 8 , 48, 16, 56, 24, 64, 32,
		39, 7 , 47, 15, 55, 23, 63, 31,
		38, 6 , 46, 14, 54, 22, 62, 30,
		37, 5 , 45, 13, 53, 21, 61, 29,
		36, 4 , 44, 12, 52, 20, 60, 28,
		35, 3 , 43, 11, 51, 19, 59, 27,
		34, 2 , 42, 10, 50, 18, 58, 26,
		33, 1 , 41, 9 , 49, 17, 57, 25
	};
	
	/* -------------------- Generate IP-1 ------------------- */
	for (uint8_t ib = 0; ib < 64 ; ib++)
	{
		Result[ib] = RLin[initialPermutation1[ib] - 1];
	}
	
}

/* .................. DES - Encrypt / Decrypt .................. */
/*
 * Function: POS_DES_CBC_DecryptBlock
 * ----------------------------------
 * The POS_DES_CBC_DecryptBlock function performs the decryption of one block of data using the DES algorithm in CBC mode.
 * 
 * Steps  :
 *         1. Key generation
 *         2. Initial permutation
 *         3. Splitting data
 *         4. Subkey shifting
 *         5. Feistel transformation
 *         6. Inverse permutation
 *         
 * Param  : 
 *         DecryptedOutput: An array of bits of the decrypted data (64 bits)
 *         InputBits: An array of bits of the encrypted data (64 bits)
 *         KEYBits: An array of bits of the decryption key (56 bits)
 *         
 * Returns: 
 *         -
 *         
 */
void POS_DES_CBC_DecryptBlock(bool *DecryptedData, bool *InputBits, bool *KEYBits)
{
	
	bool previousLeftHalf[32];
	bool expandedRightHalf[48];
	bool subKey[48];
	bool xorResult[48];
	bool sBoxOutput[32];
	bool permutedSBoxOutput[32];
	
	/* --------------- Step 1: Key generation --------------- */
	bool Kplus[56];
	POS_DES_KeyPermutation(Kplus, KEYBits); // Generate subkeys from the master key
	
	/* Split subkeys into C and D */
	bool subKeyC[28];
	POS_CopyFirstBytes(subKeyC, Kplus, 28);
	
	bool subKeyD[28];
	POS_CopyLastBytes(subKeyD, Kplus, 28, 56);
	
	/* ------------- Step 2: Initial permutation ------------ */
	bool initialPermutation[64];
	POS_DES_IPMaker(initialPermutation, InputBits); // Permute the input data
	
	/* Split the output into left and right halves */
	bool leftHalf[32];
	POS_CopyFirstBytes(leftHalf, initialPermutation, 32);
	
	bool rightHalf[32];
	POS_CopyLastBytes(rightHalf, initialPermutation, 32, 64);
	
	/* ----------- Step 3: 16 rounds of decryption ---------- */
	for (uint8_t i = 0; i < 16; i++)
	{
		bool Sh = (i == 0 || i == 1 || i == 8 || i == 15); // Shift subkeys in specific rounds
		
		POS_DES_SubKeyShift(subKeyC, Sh);
		POS_DES_SubKeyShift(subKeyD, Sh);
		
		/* ~~~~~~~~~~~~~~~ Feistel transformation ~~~~~~~~~~~~~~~ */
		for (uint8_t j = 0; j < 32; j++)
		{
			previousLeftHalf[j] = leftHalf[j]; // Save the previous left half
			leftHalf[j] = rightHalf[j]; // Swap the left and right halves
		}
		
		POS_DES_ExpandBits(expandedRightHalf, rightHalf); // Expand the right half
		POS_DES_SubKeyGenerator(subKey, subKeyC, subKeyD); // Generate the subkey for the current round
		POS_XORBits(xorResult, subKey, expandedRightHalf, 48); // XOR the subkey with the expanded right half
		POS_DES_SBoxTransformation(sBoxOutput, xorResult); // Perform the S-box operation
		POS_DES_ExpansionPermutation(permutedSBoxOutput, sBoxOutput); // Reorder the output of the S-box
		POS_XORBits(rightHalf, previousLeftHalf, permutedSBoxOutput, 32); // XOR the reordered output of the S-box with the previous left half
		
	}
	
	/* ------------- Step 4: Inverse permutation ------------ */
	bool SwappedRL[64];
	
	for (uint8_t i = 0; i < 32; i++)
	{
		/* Swap the left and right halves and prepare for the inverse permutation */
		SwappedRL[i] = rightHalf[i];
		SwappedRL[i + 32] = leftHalf[i];
	}
	
	POS_DES_IP1(DecryptedData, SwappedRL); // Perform the inverse permutation
	
}

/*
 * Function: POS_DES_CBC_Decrypt
 * -----------------------------
 * The POS_DES_CBC_Decrypt function decrypts data using the DES algorithm in CBC mode.
 *
 * Param  : 
 *         DecryptedData: A pointer to the buffer where the decrypted data will be stored.
 *         EncryptedData: A pointer to the buffer containing the encrypted data.
 *         InputLength: The length of the encrypted data in bytes.
 *         
 * Returns: 
 *         -
 *         
 */
void POS_DES_CBC_Decrypt(uint8_t *DecryptedData, uint8_t *EncryptedData, uint16_t InputLength)
{
	/* ------------- Pre-compute constant arrays ------------ */
	bool KEYBits[64] = // Predefined DES key bits
	{
		0, 0, 0, 1, 0, 0, 0, 1,
		0, 0, 0, 1, 0, 0, 0, 1,
		0, 0, 0, 1, 0, 0, 0, 1,
		0, 0, 0, 1, 0, 0, 0, 1,
		0, 0, 0, 1, 0, 0, 0, 1,
		0, 0, 0, 1, 0, 0, 0, 1,
		0, 0, 0, 1, 0, 0, 0, 1,
		0, 0, 0, 1, 0, 0, 0, 1
	};
	
	bool IV_Bits[64] = { 0 }; // Initialization Vector Bits
	
	/* ------------ Calculate padded data length ------------ */
	uint16_t length = 8 * ((uint16_t) (InputLength / 8) + 1); // Round up to next multiple of 8 bytes

	/* -------------- Copy and pad input data --------------- */
	uint8_t encryptedData[length];
	
	memcpy(encryptedData, EncryptedData, InputLength);
	memset(encryptedData + InputLength, 0x00, 8 - (InputLength % 8)); // Pad with zeros

	/* --------------- Process 8-byte blocks ---------------- */
	for (uint16_t i = 0; i < (length / 8); i++)
	{
		bool unpackedBlockBits[64]; // Array for unpacked block bits
		
		/* ~~~~~~~~~~~~ Get pointer to current block ~~~~~~~~~~~~ */
		uint8_t *block = encryptedData + (i * 8);
		
		/* ~~~~~~~~~~~~~~~~~ Unpack byte to bits ~~~~~~~~~~~~~~~~ */
		for (uint8_t j = 0; j < 8; j++)
		{
			
			uint8_t currentByte = block[j];
			
			for (uint8_t k = 0; k < 8; k++)
			{
				unpackedBlockBits[8 * j + k] = ((currentByte >> (7 - k)) & 1);
			}
			
		}
		
		/* ~~~~~~~~~~~~~~~~~ XOR with current IV ~~~~~~~~~~~~~~~~ */
		POS_XORBits(unpackedBlockBits, unpackedBlockBits, IV_Bits, 64);
		
		/* ~~~~~~~ Decrypt block using key and updated IV ~~~~~~~ */
		POS_DES_CBC_DecryptBlock(IV_Bits, unpackedBlockBits, KEYBits); // Decrypt block
		
	}
	
	/* ------------ Pack decrypted data to output ----------- */
	for (uint8_t g = 0; g < 4; g++)
	{
		DecryptedData[g] = 0;
		
		for (uint8_t j = 0; j < 8; j++)
		{
			DecryptedData[g] |= ((uint8_t) IV_Bits[8 * g + j]) << (7 - j);
		}
		
	}
	
}

/* .................. POS - Packet Processing .................. */
/*
 * Function: POS_CBC_DecryptMessage
 * --------------------------------
 * The POS_CBC_DecryptMessage function decrypts a message using the CBC mode of the DES algorithm.
 *
 * Param  : 
 *         MSG: A pointer to the message array containing the ciphertext.
 *         StartIndex: The starting index of the ciphertext within the MSG array.
 *         Index: A pointer to an integer that stores the current decryption index. This index is updated by the function to reflect the progress of decryption.
 *         
 * Returns: 
 *         -
 *         
 */
void POS_CBC_DecryptMessage(uint8_t *MSG, uint16_t StartIndex, uint16_t *Index)
{
  uint8_t CBCDES_INPUT[(*Index) - StartIndex];
  memcpy(CBCDES_INPUT, MSG + StartIndex, (*Index) - StartIndex);
  
  uint8_t CBCDES_RESULT[4];
  POS_DES_CBC_Decrypt(CBCDES_RESULT, CBCDES_INPUT, sizeof(CBCDES_INPUT));
  
  memcpy(MSG + (*Index), CBCDES_RESULT, sizeof(CBCDES_RESULT));
  (*Index) += 4;
  
}

/*
 * Function: POS_GenerateFinalTLV
 * ------------------------------
 * The POS_GenerateFinalTLV function constructs a specific data structure called "TLV" (Tag-Length-Value) based on a provided "Total Fee" string, which is likely used in a payment processing context.
 *
 * Param  : 
 *         Out: A pointer to the buffer where the generated TLV data will be stored.
 *         TotalFee: A pointer to a character string representing the total fee amount.
 *         
 * Returns: 
 *         -
 *         
 */
int32_t POS_GenerateFinalTLV(uint8_t *Out, char *TotalFee)
{
	/* 
	Packet Information
	   - Packet Length: The packet length is 29 bytes, which includes 2 bytes of packet length, 2 bytes of operation code, 4 bytes of transaction ID, 4 bytes of transaction amount, 4 bytes of transaction date, 4 bytes of transaction time, and 16 bytes of digital signature.
	   - Operation Code: The operation code is 02, which indicates a request to process a transaction.
	   - Transaction ID: The transaction ID is 12345, which is a random number.
	   - Transaction Amount: The transaction amount is 10000 Iranian Rials.
	   - Transaction Date: The transaction date is 2023-07-20.
	   - Transaction Time: The transaction time is 16:20:30.
	   - Digital Signature: The digital signature of the packet is generated using the private key of the POS device.
	*/
	
	uint16_t index = 0;
	
	Out[index++] = 0x02; // Add Start Tag (Operation Code)
	
	/* ------------------ Calculate Message Length ------------------ */
	uint16_t totalFeeLength = strlen(TotalFee);
	uint16_t messageLengthWithPadding72 = (2 * totalFeeLength) + 190;
	uint16_t messageLength = messageLengthWithPadding72 + 6;
	
	/* ---------------- Add Message Length to Buffer ---------------- */
	if (messageLengthWithPadding72 > 127)
	{
		messageLength++;
	}
	POS_AppendDecimalToArray(Out, &index, messageLength);
	
	Out[index++] = 0x00;
	Out[index++] = 0x00;
	Out[index++] = 0x00;
	Out[index++] = 0x01;
	Out[index++] = 0x72;
	
	if (messageLengthWithPadding72 > 127)
	{
		Out[index++] = 0x81;
	}
	POS_AppendDecimalToArray(Out, &index, messageLengthWithPadding72);
	
	Out[index++] = 0xB1;
	POS_AppendDecimalToArray(Out, &index, 64 + totalFeeLength);
	
	/* ------------------- Add Transaction Amount ------------------- */
	// Add Tag-Length
	Out[index++] = 0x81; // Tag
	POS_AppendDecimalToArray(Out, &index, totalFeeLength); // Length
	
	// Add Value
	for (uint16_t i = 0; i < totalFeeLength; i++)
	{
		POS_AppendDecimalToArray(Out, &index, TotalFee[i]);
	}
	
	/* ------------------ Add Transaction Time-Date ----------------- */
	// Add Tag-Length
	Out[index++] = 0x82; // Tag
	Out[index++] = 0x27; // Length (39B)
	
	// Add Transaction Time Value
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = ':';
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = '-';
	
	Out[index++] = 0x0A;
	
	// Add Transaction Date Value
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	
	Out[index++] = 0x0A;
	
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	
	Out[index++] = 0x0A;
	
	/* -------------------- Add Digital signature ------------------- */
	Out[index++] = 0x83; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x01; // Value
	
	Out[index++] = 0x84; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x03; // Value
	
	Out[index++] = 0x86; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x00; // Value
	
	Out[index++] = 0xA4;
	Out[index++] = 0x07;
	
	/* -------- Add transaction ID, which is a random number -------- */
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x90; // Tag
	Out[index++] = 0x05; // Length (5B)
	
	// Add Value
	Out[index++] = '1';
	Out[index++] = '2';
	Out[index++] = '3';
	Out[index++] = '4';
	Out[index++] = '5';
	
	/* ---------------------- Add Data Length ----------------------- */
	uint16_t StartIndex = index;
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0xB2; // Tag
	POS_AppendDecimalToArray(Out, &index, 122 + totalFeeLength); // Length-Value
	
	Out[index++] = 0xA1; // Tag
	POS_AppendDecimalToArray(Out, &index, 23 + totalFeeLength); // Length-Value
	
	/* ------------------- Add Transaction Amount ------------------- */
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x81; // Tag
	POS_AppendDecimalToArray(Out, &index, totalFeeLength); // Length
	
	// Add Value
	for (uint16_t i = 0; i < totalFeeLength; i++)
	{
		POS_AppendDecimalToArray(Out, &index, TotalFee[i]);
	}
	
	/* -------------------------------------------------------------- */
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x82; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x30; // Value
	
	Out[index++] = 0x83; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x30; // Value
	
	Out[index++] = 0x84; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x30; // Value
	
	Out[index++] = 0x85; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x30; // Value
	
	Out[index++] = 0x86; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x30; // Value
	
	Out[index++] = 0x87; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x30; // Value
	
	Out[index++] = 0x88; // Tag
	Out[index++] = 0x01; // Length (1B)
	Out[index++] = 0x30; // Value
	
	Out[index++] = 0xA2;
	Out[index++] = 0x5C;
	
	Out[index++] = 0xA1;
	Out[index++] = 0x0E;
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x81; // Tag
	Out[index++] = 0x05; // Length (5B)
	
	// Add Value
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x82; // Tag
	Out[index++] = 0x05; // Length (5B)
	
	// Add Value
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	
	Out[index++] = 0xA1;
	Out[index++] = 0x13;
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x81; // Tag
	Out[index++] = 0x0C; // Length (12B)
	
	// Add Value
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = '-';
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x82; // Tag
	Out[index++] = 0x03; // Length (3B)
	
	// Add Value
	Out[index++] = ' ';
	Out[index++] = ' ';
	Out[index++] = ' ';
	
	Out[index++] = 0xA1;
	Out[index++] = 0x0C;
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x81; // Tag
	Out[index++] = 0x04; // Length (4B)
	
	// Add Value
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = '-';
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x82; // Tag
	Out[index++] = 0x04; // Length (4B)
	
	// Add Value
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = '-';
	Out[index++] = '-';
	
	Out[index++] = 0xA1;
	Out[index++] = 0x11;
	
	/* ------------------ Add DLL Version to Buffer ----------------- */
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x81; // Tag
	Out[index++] = 0x06; // Length (6B)
	
	// Add Value
	Out[index++] = 'D';
	Out[index++] = 'l';
	Out[index++] = 'l';
	Out[index++] = 'V';
	Out[index++] = 'e';
	Out[index++] = 'r';
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x82; // Tag
	Out[index++] = 0x07; // Length (7B)
	
	// Add Value
	Out[index++] = '2';
	Out[index++] = '.';
	Out[index++] = '9';
	Out[index++] = '.';
	Out[index++] = '1';
	Out[index++] = '.';
	Out[index++] = '0';
	
	Out[index++] = 0xA1;
	Out[index++] = 0x14;
	
	/* ---------------- Add Program Version to Buffer --------------- */
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x81; // Tag
	Out[index++] = 0x06; // Length (6B)
	
	// Add Value
	Out[index++] = 'P';
	Out[index++] = 'r';
	Out[index++] = 'g';
	Out[index++] = 'V';
	Out[index++] = 'e';
	Out[index++] = 'r';
	
	/* ~~~~~~ Tag-Length-Value ~~~~~~ */
	// Add Tag-Length
	Out[index++] = 0x82; // Tag
	Out[index++] = 0x0A; // Length (10B)
	
	// Add Value
	Out[index++] = 'v';
	Out[index++] = '4';
	Out[index++] = '.';
	Out[index++] = '0';
	Out[index++] = '.';
	Out[index++] = '3';
	Out[index++] = '0';
	Out[index++] = '3';
	Out[index++] = '1';
	Out[index++] = '9';
	
	/* -------------------------------------------------------------- */
	POS_CBC_DecryptMessage(Out, StartIndex, &index);
	
	return index;
	
}

/* ..................... POS - Transaction ..................... */
/*
 * Function: POS_SendTransaction
 * -----------------------------
 * The POS_SendTransaction function transmit a transaction to a POS terminal.
 *
 * Param  : 
 *         POS: A pointer to the POS structure containing relevant information about the terminal.
 *         TotalFee: A string representing the total transaction fee.
 *         Timeout: The timeout value in milliseconds for waiting for a response.
 *         
 * Returns: 
 *         POS_OK / POS_ERROR
 *         
 * Example:
 *         uint8_t data;
 *         char TotalFee[] = "10000";
 *         
 *         POS_TypeDef MainPOS;
 *         
 *         void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 *         {
 *               POS_UART_ISRHandle(&MainPOS, data);
 *               HAL_UART_Receive_IT(&huart2, &data, 1); 
 *         }
 *
 *         int main(void)
 *         {
 *               MainPOS.UARTx = &huart2;
 *               
 *               HAL_UART_Receive_IT(&huart2, &data, 1);
 *               
 *               POS_SendTransaction(&MainPOS, TotalFee, 30000);
 *               
 *               while(1)
 *               {
 *                      POS_TimingHandle(&MainPOS);
 *               }
 *         }
 *
 */
POS_StatusTypeDef POS_SendTransaction(POS_TypeDef *POS, char *TotalFee, uint32_t Timeout)
{
	
	uint16_t Size = 0;
	uint8_t  transactionPacket[280];
	
	if (POS->TransactionStatus == POS_SEND_TRANSACTION_ENDED)
	{
		
		/* ------------------- Clear Rx Buffer ------------------ */
		POS_UART_ClearBuffer(POS);
		
		/* ------------------- Generate Packet ------------------ */
		Size = POS_GenerateFinalTLV(transactionPacket, TotalFee);
		
		/* -------------------- Set Timeout --------------------- */
		POS->PreRxCounter      = 0;
		POS->RespTimeout       = POS_GetTick() + Timeout;
		POS->TransactionStatus = POS_SEND_TRANSACTION_STARTED;
		
		/* ------------------- Transmit Packet ------------------ */
		#ifdef USE_HAL_DRIVER
		
		return (POS_StatusTypeDef)POS_UART_Transmit(POS->UARTx, transactionPacket, Size);
		
		#else
		
		return (POS_StatusTypeDef)POS_UART_Transmit(transactionPacket, Size, POS_UART_TX_TIMEOUT);
		
		#endif // USE_HAL_DRIVER
		
	}
	
	return POS_ERROR;
	
}

/*
 * Function: POS_GetTransactionResult
 * ----------------------------------
 * The POS_GetTransactionResult function parses a received POS packet and returns the transaction result.
 *
 * Param  : 
 *         ReceivedTLV: A pointer to the received TLV data packet.
 *         Length: The length of the received data packet.
 *         
 * Returns: 
 *         TRANSACTION_SUCCESS
 *         TRANSACTION_CANCEL
 *         TRANSACTION_WRONG_PASSWORD
 *         TRANSACTION_POS_TIMEOUT
 *         TRANSACTION_NETWORK_ERROR
 *         TRANSACTION_INSUFFICIENT_FUNDS
 *         TRANSACTION_TIMEOUT
 *         TRANSACTION_WRONG_RESULT
 *         TRANSACTION_PACKET_ERROR
 *
 */
POS_TransactionResultTypeDef POS_GetTransactionResult(uint8_t *ReceivedTLV, uint16_t Length)
{

	/* POS Packet Sample

		Payment Cancel:
		00 00 00 00 00 00 72 06 b1 04 88 02 01 03         ......r.�.�...

		Payment Timeout:
		00 00 00 00 00 00 72 06 b1 04 88 02 01 01         ......r.�.�...

		Password Wrong:
		00 00 00 00 00 00 72 06 b1 04 88 02 01 37         ......r.�.�..7

		Payment OK:
		00 00 00 00 00 00 72 66 b1 64 85 06 30 30 30 30   ......rf�d�.0000
		34 34 8e 05 31 30 30 30 30 8d 05 31 30 30 30 30   44�.10000�.10000
		8c 06 37 32 31 30 32 39 8b 0c 38 33 37 37 35 38   �.697029�.201758
		31 38 32 35 37 33 8a 10 35 30 34 37 30 36 31 30   182393�.50470610
		33 33 33 33 38 35 34 38 89 08 31 33 37 30 31 32   66338841�.137012
		39 39 88 02 01 00 87 13 31 34 30 32 2f 31 31 2f   99�...�.1402/11/
		32 32 20 30 36 3a 31 38 3a 32 39 86 01 31         22 06:18:29�.1

	*/
	
	uint16_t index = 0;
	uint8_t  tlv_len = 0;
	uint8_t  tlv_val = 0;
	
	/* -------------------------------------------------------------- */
	for (; index < Length; index++)
	{
		
		/* ~~~~~~~~~~~~~~~~~~~~~~~ Check Start Tag ~~~~~~~~~~~~~~~~~~~~~~ */
		if (ReceivedTLV[index] == POS_TLV_TAG_START)
		{
			
			index++;
			tlv_len = ReceivedTLV[index];
			tlv_val = ReceivedTLV[index + tlv_len];
			
			/* ,,,,,,,,,,,,,,,,,,,,, Check Result Length ,,,,,,,,,,,,,,,,,,,, */
			if ((index + tlv_len + 1) != Length)
			{
				return TRANSACTION_PACKET_ERROR;
			}
			
			/* ,,,,,,,,,,,,,,,, Check Transaction Result Tag ,,,,,,,,,,,,,,,, */
			if ((tlv_val == POS_TLV_VAL_TRANSACTION_OK) ||
				(tlv_val == POS_TLV_VAL_TRANSACTION_CANCEL) ||
				(tlv_val == POS_TLV_VAL_TRANSACTION_WRONG_PASSWORD) ||
				(tlv_val == POS_TLV_VAL_TRANSACTION_TIMEOUT) ||
				(tlv_val == POS_TLV_VAL_TRANSACTION_NETWORK_ERROR) ||
				(tlv_val == POS_TLV_VAL_TRANSACTION_INSUFFICIENT_FUNDS)
				)
			{
				return (POS_TransactionResultTypeDef)tlv_val;
			}
			else
			{
				return TRANSACTION_WRONG_RESULT;
			}
			
		}
		
	}
	
	/* -------------------------------------------------------------- */
	return TRANSACTION_PACKET_ERROR;
	
}

/*
 * Function: POS_GetTransactionInfo
 * --------------------------------
 * The POS_GetTransactionInfo function parses parameters of the transaction result.
 *
 * Param  : 
 *         ReceivedTLV: A pointer to the received TLV data packet.
 *         Length: The length of the received data packet.
 *         
 * Returns: 
 *         Transaction Parameters
 *
 */
POS_TransactionInfoTypeDef POS_GetTransactionInfo(uint8_t *ReceivedTLV, uint16_t Length)
{

	/* POS Packet Sample

		Payment Cancel:
		00 00 00 00 00 00 72 06 b1 04 88 02 01 03         ......r.�.�...

		Payment Timeout:
		00 00 00 00 00 00 72 06 b1 04 88 02 01 01         ......r.�.�...

		Password Wrong:
		00 00 00 00 00 00 72 06 b1 04 88 02 01 37         ......r.�.�..7

		Payment OK:
		00 00 00 00 00 00 72 66 b1 64 85 06 30 30 30 30   ......rf�d�.0000
		34 34 8e 05 31 30 30 30 30 8d 05 31 30 30 30 30   44�.10000�.10000
		8c 06 37 32 31 30 32 39 8b 0c 38 33 37 37 35 38   �.697029�.201758
		31 38 32 35 37 33 8a 10 35 30 34 37 30 36 31 30   182393�.50470610
		33 33 33 33 38 35 34 38 89 08 31 33 37 30 31 32   66338841�.137012
		39 39 88 02 01 00 87 13 31 34 30 32 2f 31 31 2f   99�...�.1402/11/
		32 32 20 30 36 3a 31 38 3a 32 39 86 01 31         22 06:18:29�.1

	*/

	uint8_t  copyIndex = 0;
	uint16_t pIndex    = 0;
	
	uint8_t  tlv_len = 0;
	
	uint32_t feeMultiplier = 1;

	POS_TransactionInfoTypeDef transaction = { 0 };
	
	/* ------------------------- Fee Processing ------------------------- */
	while ((pIndex < Length) && (ReceivedTLV[pIndex] != POS_TLV_TAG_FEE)) // Start of Fee
	{
		pIndex++;
	}
	
	pIndex++;
	
	tlv_len = ReceivedTLV[pIndex];
	
	/* ..... Calculate Fee ..... */
	for (copyIndex = tlv_len; copyIndex > 0; copyIndex--)
	{
		transaction.Fee += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex + copyIndex]) * feeMultiplier);
		feeMultiplier   *= 10;
	}
	
	pIndex += tlv_len;
	
	/* ------------------- Tracking Number Processing ------------------- */
	while ((pIndex < Length) && (ReceivedTLV[pIndex] != POS_TLV_TAG_TRACKING_NUMBER)) // Start of Reference Number
	{
		pIndex++;
	}

	pIndex++;
	
	tlv_len = ReceivedTLV[pIndex];
	
	pIndex++;

	/* ..... Copy Tracking Number ..... */
	for (copyIndex = 0; (copyIndex < tlv_len) && (copyIndex < POS_TLV_LEN_TRACKING_NUMBER); pIndex++, copyIndex++)
	{
		transaction.TrackingNumber[copyIndex] = ReceivedTLV[pIndex];
	}
	
	/* ------------------- Reference Number Processing ------------------ */
	while ((pIndex < Length) && (ReceivedTLV[pIndex] != POS_TLV_TAG_REFERENCE_NUMBER)) // Start of Reference Number
	{
		pIndex++;
	}

	pIndex++;
	
	tlv_len = ReceivedTLV[pIndex];
	
	pIndex++;

	/* ..... Copy Reference Number ..... */
	for (copyIndex = 0; (copyIndex < tlv_len) && (copyIndex < POS_TLV_LEN_REFERENCE_NUMBER); pIndex++, copyIndex++)
	{
		transaction.ReferenceNumber[copyIndex] = ReceivedTLV[pIndex];
	}
	
	/* --------------------- Card Number Processing --------------------- */
	while ((pIndex < Length) && (ReceivedTLV[pIndex] != POS_TLV_TAG_CARD_NUMBER)) // Start of Card NUmber
	{
		pIndex++;
	}

	pIndex++;
	
	tlv_len = ReceivedTLV[pIndex];
	
	pIndex++;

	/* ..... Copy Card Number ..... */
	for (copyIndex = 0; (copyIndex < tlv_len) && (copyIndex < POS_TLV_LEN_CARD_NUMBER); pIndex++, copyIndex++)
	{
		transaction.CardNumber[copyIndex] = ReceivedTLV[pIndex];
	}
	
	/* --------------------- Terminal ID Processing --------------------- */
	while ((pIndex < Length) && (ReceivedTLV[pIndex] != POS_TLV_TAG_TERMINAL_ID)) // Start of Terminal ID
	{
		pIndex++;
	}

	pIndex++;
	
	tlv_len = ReceivedTLV[pIndex];
	
	pIndex++;

	/* ..... Copy Terminal ID ..... */
	for (copyIndex = 0; (copyIndex < tlv_len) && (copyIndex < POS_TLV_LEN_TERMINAL_ID); pIndex++, copyIndex++)
	{
		transaction.TerminalID[copyIndex] = ReceivedTLV[pIndex];
	}
	
	/* ---------------------- Date/Time Processing ---------------------- */
	while ((pIndex < Length) && (ReceivedTLV[pIndex] != POS_TLV_TAG_DATE_TIME)) // Start of Terminal ID
	{
		pIndex++;
	}

	pIndex++;
	
	tlv_len = ReceivedTLV[pIndex];
	
	pIndex++;

	/* ..... Date Processing ..... */
	transaction.Year += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex]) * 1000), pIndex++;
	transaction.Year += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex]) * 100), pIndex++;
	transaction.Year += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex]) * 10), pIndex++;
	transaction.Year += __POS_ASCII_TO_NUM(ReceivedTLV[pIndex]), pIndex++;

	pIndex++;

	transaction.Month += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex]) * 10), pIndex++;
	transaction.Month += __POS_ASCII_TO_NUM(ReceivedTLV[pIndex]), pIndex++;
	pIndex++;

	transaction.Day += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex]) * 10), pIndex++;
	transaction.Day += __POS_ASCII_TO_NUM(ReceivedTLV[pIndex]), pIndex++;
	pIndex++;

	/* ..... Time Processing ..... */
	transaction.Hour += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex]) * 10), pIndex++;
	transaction.Hour += __POS_ASCII_TO_NUM(ReceivedTLV[pIndex]), pIndex++;
	pIndex++;

	transaction.Minute += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex]) * 10), pIndex++;
	transaction.Minute += __POS_ASCII_TO_NUM(ReceivedTLV[pIndex]), pIndex++;
	pIndex++;

	transaction.Second += (__POS_ASCII_TO_NUM(ReceivedTLV[pIndex]) * 10), pIndex++;
	transaction.Second += __POS_ASCII_TO_NUM(ReceivedTLV[pIndex]), pIndex++;
	pIndex++;

	/* ------------------------------------------------------------------ */
	return transaction;

}

/* ..................... POS - ISR Handler ..................... */
/*
 * Function: POS_UART_ISRHandler
 * -----------------------------
 * UART Rx IRQ handling
 *
 * Param  : 
 *         POS: Pointer to POS Device Type
 *         uData: Received byte from UART
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         uint8_t data;
 *         POS_TypeDef MainPOS;
 *
 *         void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 *         {
 *               POS_UART_ISRHandle(&MainPOS, data);
 *               HAL_UART_Receive_IT(&huart2, &data, 1);
 *         }
 *         
 */
void POS_UART_ISRHandler(POS_TypeDef *POS, uint8_t uData)
{
	
	POS->RxBuffer[POS->RxCounter] = uData;
	POS->RxCounter++;
	
}

/*
 * Function: POS_TimingHandler
 * ---------------------------
 * The POS_TimingHandler function manages the timeout and response handling for a transaction initiated with the POS_SendTransaction function. It checks for response data within a specified timeout, processes the received data, and triggers a callback function with the transaction result.
 *
 * Param  : 
 *         POS: Pointer to POS Device Type
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         uint8_t data;
 *         char TotalFee[] = "10000";
 *
 *         POS_TypeDef MainPOS;
 *
 *         void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 *         {
 *               POS_UART_ISRHandle(&MainPOS, data);
 *               HAL_UART_Receive_IT(&huart2, &data, 1);
 *         }
 *
 *         int main(void)
 *         {
 *               MainPOS.UARTx = &huart2;
 *
 *               HAL_UART_Receive_IT(&huart2, &data, 1);
 *
 *               POS_SendTransaction(&MainPOS, TotalFee, 30000);
 *
 *               while(1)
 *               {
 *                      POS_TimingHandle(&MainPOS);
 *               }
 *         }
 *         
 */
void POS_TimingHandler(POS_TypeDef *POS)
{
	
	uint32_t CurTick = POS_GetTick();
	
	POS_TransactionInfoTypeDef transaction = {0};
	
	POS_TransactionResultTypeDef responseCode = TRANSACTION_WRONG_RESULT;
	
	/* ---------------- Check Send Transaction Status --------------- */
	if (POS->TransactionStatus == POS_SEND_TRANSACTION_STARTED)
	{
		
		/* ~~~~~~~~~~~~~~~~~~~ Check Response Timeout ~~~~~~~~~~~~~~~~~~~ */
		if (POS->RespTimeout > CurTick)
		{
			
			/* ,,,,,,,,,,,,,,,,,,, Check UART Rx Timeout ,,,,,,,,,,,,,,,,,,,, */
			if ((CurTick - POS->RxUpdateTime) > POS_UART_RX_TIMEOUT)
			{
				
				/* ::::::::::::::::: Check Received Packet Size ::::::::::::::::: */
				if (POS->PreRxCounter == POS->RxCounter)
				{
					
					if (POS->RxCounter > 2)
					{
						
						/* ======================= Check Response ======================= */
						responseCode = POS_GetTransactionResult(POS->RxBuffer, POS->RxCounter);
						
						if (responseCode == TRANSACTION_SUCCESS)
						{
							transaction = POS_GetTransactionInfo(POS->RxBuffer, POS->RxCounter);
						}
						
						
						/* ======================== Clear Buffer ======================== */
						POS_UART_ClearBuffer(POS);
						
						/* ======================== Run Callback ======================== */
						POS_TransactionCallback(responseCode, transaction);
						
						POS->TransactionStatus = POS_SEND_TRANSACTION_ENDED;
						
					}
					
				}
				else
				{
					/* ===================== Update UART Rx Time ==================== */
					POS->PreRxCounter = POS->RxCounter;
					POS->RxUpdateTime = POS_GetTick();
				}
				
			}
			
		}
		else
		{
			
			/* ,,,,,,,,,,,,,,,,,,,,,,,, Run Callback ,,,,,,,,,,,,,,,,,,,,,,,, */
			POS_TransactionCallback(TRANSACTION_TIMEOUT, transaction);
			
			POS->TransactionStatus = POS_SEND_TRANSACTION_ENDED;
			
		}
		
	}
	
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
