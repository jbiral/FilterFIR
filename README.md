# FilterFIR #

## Implements a FIR filter using generated coefficients for Teensy ##

### Description ###
This small library implements a FIR filter by providing the array of coefficients. Those coefficient must be coded on 16 bits (signed) and can be easily calculated on tools such as MATLAB (fdatool). The vector filtered must be coded on 16 bits signed too.

### Example ###
Here's a simple example that shows how to use the library:
...c
int N; // The number of taps of the filter
const int16_t coeff[N] = { 1, 0, 0, 0 } // The coefficients of the filter

// Create the filter object
FIR<N> fir;

// Set the coefficients and calculate the gain automatically
fir.setCoefficients(coeff);

// Process the input vector of length inputSize
for(int i=0; i<inputSize; i++)
{
	inputFiltered[i] = fir.process(input[i]);
}
...

**Be careful** that the coefficients of the filter and the input vector must be coded on 16 bits (signed) to avoid an overflow in the multiplication process.
