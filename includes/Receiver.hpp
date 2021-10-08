
#ifndef RECEIVER_HPP
# define RECEIVER_HPP

# include <iostream>
# include <irrKlang.h>
# include <ik_ISoundMixedOutputReceiver.h>
using namespace irrklang;

class	Receiver : public ISoundMixedOutputReceiver
{
	private:
		float frequency[];
	public:
		void	OnAudioDataReady(const void* data, int byteCount, int playbackrate);
};

#endif