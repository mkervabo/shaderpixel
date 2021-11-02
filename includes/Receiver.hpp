/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Receiver.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiwenn <maiwenn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:47:50 by maiwenn           #+#    #+#             */
/*   Updated: 2021/11/02 15:47:52 by maiwenn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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