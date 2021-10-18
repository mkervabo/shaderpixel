#include "Receiver.hpp"
#include <stdint.h>

Receiver::Receiver()
{
	this->i = 0;
	this->size = 512;
	this->in = (float*)fftwf_alloc_real(this->size);
    this->out = (float*)fftwf_alloc_real(this->size);
    this->p = fftwf_plan_r2r_1d(this->size, in, out, FFTW_R2HC, FFTW_ESTIMATE);
}

//	data			representing the sound frames which just have been mixed.
//					Sound data always consists of two interleaved sound channels
//					at 16bit per frame. 2 * 16 = 32
//	byteCount		Amount of bytes of the data 1bytes = 8 bits
//	playbackrate	The playback rate at samples per second (usually something
//					like 44000). This value will not change and always båe the 
//					same for an instance of an ISoundEngine.
void	Receiver::OnAudioDataReady(const void* data, int byteCount, int playbackrate)
{
	int j = 0;
	(void)playbackrate;

	while(j < byteCount / 4)
	{
		this->in[i] = (float)((int16_t*)data)[j * 2];
		this->i++;
		j++;
		if (this->i == this->size)
		{
			fftwf_execute(this->p); /* repeat as needed */
			float max = 0;
			for(size_t k = 0; k < this->size; k++)
			{
				if (this->out[k] > max)
					max = this->out[k];
			}
			for(size_t k = 0; k < this->size; k++)
			{
				if (this->out[k] < 0)
					this->out[k] = 0;
				else
					this->out[k] /= max;
			}
			this->i = 0;
		}	
	}
}

size_t	Receiver::getSize()
{
	return(this->size);
}

float	*Receiver::getOut()
{
	return(this->out);
}


Receiver::~Receiver()
{
	fftwf_free(this->in); 
	fftwf_free(this->out);

	fftwf_destroy_plan(this->p);
	
}