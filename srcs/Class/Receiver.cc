#include "Receiver.hpp"
#include <fftw3.h>

//	data			representing the sound frames which just have been mixed.
//					Sound data always consists of two interleaved sound channels
//					at 16bit per frame. 2 * 16 = 32
//	byteCount		Amount of bytes of the data 1bytes = 8 bits
//	playbackrate	The playback rate at samples per second (usually something
//					like 44000). This value will not change and always båe the 
//					same for an instance of an ISoundEngine.
void	Receiver::OnAudioDataReady(const void* data, int byteCount, int playbackrate)
{
	int N = byteCount / 4;
	fftw_complex in[N], out[N];//double[]
	int i = 0;
	int j = 0;
	while(i < byteCount / 2)
	{
		in[j][0] = (float)((short*)data)[i];
		i += 2;
		j++;
	} 
	fftw_plan p;
	p = fftw_create_plan(N, FFTW_FORWARD, FFTW_ESTIMATE); 
	//http://www.fftw.org/fftw2_doc/fftw_3.html#SEC23
	// FFTW_FORWARD/FFTW_BACKWAR | FFTW_ESTIMATE/FFTW_MEASURE
	//...
	fftw_one(p, in, out);
	//...
	fftw_destroy_plan(p);
	//this->frequency = out;
	for(int k = 0; k < N; k++)
	{
		printf("in : %f. out: %f\n", in[k][0], out[k][0]);
	}
	//frequency = out;
}