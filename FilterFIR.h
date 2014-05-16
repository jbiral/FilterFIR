#ifndef FILTERFIR_H
#define FILTERFIR_H

#include <cstdint>

template<int filterTaps>
class FIR {

private:
	int16_t values[filterTaps];	
	int16_t coef[filterTaps];
	float gain; // set to 1 and input unity to see what this needs to be	
	int k; // k stores the index of the current array read to create a circular memory through the array

public:
	FIR(){
		k = 0; //initialize so that we start to read at index 0
		for (int i=0; i<filterTaps; i++) {      
			values[i] = 0; // to have a nice start up, fill the array with 0's
		}
		//TODO calculate default gain?
		//TODO calculate default coefs?
	}
	
	FIR(int newGain, float *newCoefs) {
		k = 0; //initialize so that we start to read at index 0
		setGain(newGain);
		for (int i=0; i<filterTaps; i++) {      
			values[i] = 0; // to have a nice start up, fill the array with 0's
		}
		setCoefficients(newCoefs);
	}

	void setGain(float newGain) {
		gain = newGain;
	}
	
	void setCoefficients(const int16_t *newCoefs) {
		for (int i=0; i<filterTaps; i++) {      
			coef[i] = newCoefs[i];
		}
	}
	
	void setCoefficient(int idx, int16_t newCoef) { 
		coef[idx] = newCoef; 
	}
	
	int16_t process(int16_t in) {
                // Input and coefficients are coded on 16 bits. To avoid overflow in the multiplication process, the output must be coded on 32 bits.
		int32_t out = 0;
                
                // Store the input of the routine (contents of the 'in' variable) in the array at the current pointer position
		values[k] = in;

		for (int i=0; i<filterTaps; i++)
                {
			out += (int32_t) coef[i] * (int32_t) values[(i + k) % filterTaps];
		}
                
                // Shift by 15 bits to the right (16 bits signed) to rescale the output
		out = out >> 15;
                out = (int16_t) (gain * (float) out);

		k = (k+1) % filterTaps;            // k is increased and wraps around the filterTaps, so next time we will overwrite the oldest saved sample in the array

		return ((int16_t) out);                              // we send the output value back to whoever called the routine
	}
};

#endif
