// $Id: ugen_JuceMIDIMostRecentNote.h 350 2011-07-22 09:07:56Z 0x4d52 $
// $HeadURL: http://ugen.googlecode.com/svn/trunk/UGen/juce/io/ugen_JuceMIDIMostRecentNote.h $

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

#ifndef _UGEN_ugen_JuceMIDIMostRecentNote_H_
#define _UGEN_ugen_JuceMIDIMostRecentNote_H_

#ifndef UGEN_NOEXTGPL

#include "../../core/ugen_UGen.h"
#include "../../core/ugen_ExternalControlSource.h"
#include "ugen_JuceMIDIInputBroadcaster.h"


class MIDIMostRecentNoteInternal :  public JuceMIDIInputListener,
									public ExternalControlSourceInternal
{
public:
	MIDIMostRecentNoteInternal(const int midiChannel,
							   const float minVal, const float maxVal, 
							   const ExternalControlSource::Warp warp, 
							   void* port) throw();
	
	void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) throw();
	
private:
	int midiChannel_;
	void* port_;
};

DeclareJuceMIDIDataSourceNoDefault(MIDIMostRecentNote, 
								   (midiChannel, minVal, maxVal, warp, port), 
								   (const int midiChannel = 1,
									const float minVal = 0.f, const float maxVal = 127.f, 
									const ExternalControlSource::Warp warp = ExternalControlSource::Linear, 
									void* port = 0),
									lagTime,
								   (const int midiChannel = 1,
									const float minVal = 0.f, const float maxVal = 127.f, 
									const ExternalControlSource::Warp warp = ExternalControlSource::Linear, 
									const double lagTime = 0.1,
									void* port = 0));

#endif // gpl

#endif // _UGEN_ugen_JuceMIDIMostRecentNote_H_
