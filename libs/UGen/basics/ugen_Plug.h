// $Id: ugen_Plug.h 355 2011-10-30 06:44:25Z 0x4d52 $
// $HeadURL: http://ugen.googlecode.com/svn/trunk/UGen/basics/ugen_Plug.h $

/*
 ==============================================================================
 
 This file is part of the UGEN++ library
 Copyright 2008-11 The University of the West of England.
 by Martin Robinson
 
 ------------------------------------------------------------------------------
 
 UGEN++ can be redistributed and/or modified under the terms of the
 GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.
 
 UGEN++ is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with UGEN++; if not, visit www.gnu.org/licenses or write to the
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA
 
 The idea for this project and code in the UGen implementations is
 derived from SuperCollider which is also released under the 
 GNU General Public License:
 
 SuperCollider real time audio synthesis system
 Copyright (c) 2002 James McCartney. All rights reserved.
 http://www.audiosynth.com
 
 ==============================================================================
 */

#ifndef _UGEN_ugen_Plug_H_
#define _UGEN_ugen_Plug_H_

#include "../core/ugen_UGen.h"
#include "../core/ugen_UGenArray.h"

/** A UGenInternal which allows repatching.
 This allows its source UGen to be changed after construction optionally with a crossfade. 
 @ingroup UGenInternals */
class PlugUGenInternal : public ProxyOwnerUGenInternal,
                         public DoneActionSender
{
public:
	PlugUGenInternal(UGen const& source, bool shouldAllowAutoDelete = true) throw();
	void prepareForBlock(const int actualBlockSize, const unsigned int blockID, const int channel) throw();
	void processBlock(bool& shouldDelete, const unsigned int blockID, const int channel) throw();
	
	void releaseInternal() throw();
	void stealInternal() throw();
	
	/**
	 Change the source of the Plug.
	 
	 Be careful when calling this from a separate thread from the audio processing thread
	 and use locks appropriately. Previous sources are retained by default so that their
	 processing still continues should the Plug be switched back to  a previous source
	 in the future. This means (for example) a soundfile playing back will not start where
	 it had reach just before the source was switched but will start where it would have 
	 reached had it continued to play.
	 
	 @param		source						The new source.
	 @param		releasePreviousSources		Whether to retain previous sources and continue 
											to force them to process.
	 @param		fadeTime					Time in seconds to crossfade to the new source.
	 */
	bool setSource(UGen const& source, const bool releasePreviousSources = false, const float fadeTime = 0.f);
		
	UGen& getSource();
	
protected:
	UGenArray sources;
	int currentSourceIndex;
	int fadeSourceIndex;
	float currentSourceFadeLevel, fadeSourceFadeLevel, fadeTime, deltaFade;
	bool releasePreviousSourcesAfterFade;
	UGenArray tempSource;
	bool shouldAllowAutoDelete_;
};


#define Plug_Docs	@param source	The initial source of the Plug. The number of channels this Plug can			\
									support is governed by the number of channels in this original source			\
									UGen. You could use UGen::emptyChannels() to initialise a Plug with				\
									a specific number of channels. The source may be changed later using			\
									UGen::setSource(), UGen::fadeSource()											\
					@param shouldAllowAutoDelete	If true this behaves like most other UGen classes				\
													i.e., it may be deleted by a DoneAction (e.g., an envelope		\
													ending). If false this protects UGen instances further up		\
													the chain (and itself) from being deleted by DoneActions.

/** A UGen which allows repatching.
 This allows its source UGen to be changed after construction optionally with a crossfade. 
 @ingroup AllUGens ControlUGens EnvUGens
 @see UGen::setSource(), UGen::fadeSource() */
UGenSublcassDeclaration(Plug, 
						(source, shouldAllowAutoDelete), 
						(UGen const& source, bool shouldAllowAutoDelete = true), 
						COMMON_UGEN_DOCS Plug_Docs);

#endif // _UGEN_ugen_Plug_H_
