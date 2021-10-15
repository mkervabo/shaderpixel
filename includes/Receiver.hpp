
#ifndef RECEIVER_HPP
# define RECEIVER_HPP

# include <iostream>
# include <irrKlang.h>
# include <ik_ISoundMixedOutputReceiver.h>
using namespace irrklang;

# include <fftw3.h>

class	Receiver : public ISoundMixedOutputReceiver
{
	private:
		fftwf_plan p;
		float *in;
		float *out;
		size_t size;
		size_t i;
	public:
		Receiver();
		virtual void	OnAudioDataReady(const void* data, int byteCount, int playbackrate);
		size_t			getSize();
		float			*getOut();
		virtual ~Receiver();
};

#endif