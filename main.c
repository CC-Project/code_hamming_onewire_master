// Include dependencies
#include "../code_hamming/src/hamming.h"
#include "../code_hamming/src/matrix.h"

#include "../lib_data/data.h"
#include "../lib_uart/uart.h"
#include "../lib_utilities/utilities.h"

#include "../com_onewire_master/config.h"
#include "../com_onewire_master/src/onewire.h"

// Configuration
#include "config.h"
#include <string.h>

int main(void)
{
    // Generate Hamming configuration
    struct Hamming_config* hamming_config = hamming_generate_config();

    uint32_t nb_data = 512;
    char data_string[] = "01000010011011110110111001101010011011110111010101110010001011000010000001101010011001010010000001110011011101010110100101110011001000000110110001100101001000000111000001110010011001010110110101101001011001010111001000100000011101000110010101111000011101000110010100100000011001000110010100100000011011000010011101101000011010010111001101110100011011110110100101110010011001010010000001100100011001010010000001101100001001110110100001110101011011010110000101101110011010010111010011000011101010010010000000100001";

    uint8_t remainder = nb_data % K; // Data number which will not be encoded
    uint8_t p;

    struct Matrix* data_loaded = matrix_generate(K, 1);

    // Send number of data
    for(uint8_t i = 0; i < 32; i++)
        ow_write_bit((nb_data & _BV(i)) ? 1 : 0);

    _delay_us(100);

    // Send encoded data
    for(uint32_t i = 0; i < nb_data; i--)
    {
        if(i % K == K - 1)
        {
            matrix_set(data_loaded, (i % K) + 1, 1, (data_string[nb_data - 1 - i] == 0x31) ? 1 : 0);
            struct Matrix* data_encoded = hamming_encode(data_loaded, hamming_config);

            for(p = 0; p < N; p++)
                //ow_write_bit(matrix_get(data_encoded, p + 1, 1));
                matrix_show(data_encoded);

            matrix_free(data_encoded);
            _delay_us(10);
        }
        else
        {
            matrix_set(data_loaded, (i % K) + 1, 1, (data_string[nb_data - 1 - i] == 0x31) ? 1 : 0);
            data_show(data_loaded->data);
        }
    }
    /*
    // Remainder
    if(remainder != 0)
    {
        // Void other data than remainder
        for(p = remainder + 1; p < K; p++)
            matrix_set(data_loaded, j, 1, 0);

        // Encode
        struct Matrix* data_encoded = hamming_encode(data_loaded, hamming_config);

        // Send by one_wire
        for(p = 0; p < N; p++)
            ow_write_bit(matrix_get(data_encoded, p + 1, 1));

        matrix_free(data_encoded);
    }
    */
    matrix_free(data_loaded);
    return 0;
}
