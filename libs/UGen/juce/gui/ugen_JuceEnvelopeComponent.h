// $Id: ugen_JuceEnvelopeComponent.h 350 2011-07-22 09:07:56Z 0x4d52 $
// $HeadURL: http://ugen.googlecode.com/svn/trunk/UGen/juce/gui/ugen_JuceEnvelopeComponent.h $

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

#ifndef UGEN_JUCEENVELOPECOMPONENT_H
#define UGEN_JUCEENVELOPECOMPONENT_H

#ifndef UGEN_NOEXTGPL

#include "../../core/ugen_UGen.h"
#include "../../envelopes/ugen_Env.h"
#include "../../core/ugen_Text.h"
#include "../../gui/ugen_GUI.h"
#include "../ugen_JuceUtility.h"

#define HANDLESIZE 7
#define FINETUNE 0.001

//#define MYDEBUG 1 // get rid of this later

class EnvelopeComponent;
class EnvelopeHandleComponent;
class EnvelopeLegendComponent;

class EnvelopeHandleComponentConstrainer :	public ComponentBoundsConstrainer
{
public:
	EnvelopeHandleComponentConstrainer(EnvelopeHandleComponent* handle);
	
	void checkBounds (Rectangle<int>& bounds,
					  const Rectangle<int>& old, const Rectangle<int>& limits,
					  bool isStretchingTop, bool isStretchingLeft,
					  bool isStretchingBottom, bool isStretchingRight);
	
	void setAdjacentHandleLimits(int setLeftLimit, int setRightLimit);
	
private:
	int leftLimit, rightLimit;
	EnvelopeHandleComponent* handle;
};

class EnvelopeHandleComponent :	public Component
{
public:	
	EnvelopeHandleComponent();
	EnvelopeComponent* getParentComponent() const;
	
	void updateTimeAndValue();
	
	void updateLegend();
	void paint(Graphics& g);
	void moved();
		
	void mouseMove         (const MouseEvent& e);
    void mouseEnter        (const MouseEvent& e);
    void mouseExit         (const MouseEvent& e);
    void mouseDown         (const MouseEvent& e);
    void mouseDrag         (const MouseEvent& e);
    void mouseUp           (const MouseEvent& e);
		
	EnvelopeHandleComponent* getPreviousHandle() const;
	EnvelopeHandleComponent* getNextHandle() const;
	void removeThisHandle();
	
	void setMousePositionToThisHandle();
	
	void resetOffsets() { offsetX = offsetY = 0; }
	double getTime() const	{ return time;	}
	double getValue() const	{ return value; }
	EnvCurve getCurve() const	{ return curve; }
	int getHandleIndex() const;
		
	void setTime(double timeToSet);
	void setValue(double valueToSet);
	void setCurve(EnvCurve curveToSet);
	void setTimeAndValue(double timeToSet, double valueToSet, double quantise = 0.0);
	void offsetTimeAndValue(double offsetTime, double offsetValue, double quantise = 0.0);
	double constrainDomain(double domainToConstrain) const;
	double constrainValue(double valueToConstrain) const;
	
	friend class EnvelopeComponent;
	
private:
	bool dontUpdateTimeAndValue;
	void recalculatePosition();
	
	ComponentDragger dragger;
	int lastX, lastY;
	int offsetX, offsetY;
	EnvelopeHandleComponentConstrainer resizeLimits;
	
	double time, value;
	EnvCurve curve;
	bool ignoreDrag;
};


class EnvelopeComponentListener
{
public:
	EnvelopeComponentListener() throw() {}
	virtual ~EnvelopeComponentListener() {}
	virtual void envelopeChanged(EnvelopeComponent* changedEnvelope) = 0;
};

/** For displaying and editing a breakpoint envelope. 
 @ingoup EnvUGens
 @see Env */
class EnvelopeComponent : public Component
{
public:
	EnvelopeComponent();
	~EnvelopeComponent();
	
	void setDomainRange(const double min, const double max);
	void setDomainRange(const double max) { setDomainRange(0.0, max); }
	void getDomainRange(double& min, double& max) const;
	void setValueRange(const double min, const double max);
	void setValueRange(const double max) { setValueRange(0.0, max); }
	void getValueRange(double& min, double& max) const;
	
	enum GridMode { 
		GridLeaveUnchanged = -1,
		GridNone = 0,
		GridValue = 1, 
		GridDomain = 2, 
		GridBoth = GridValue | GridDomain 
	};
	void setGrid(const GridMode display, const GridMode quantise, const double domain = 0.0, const double value = 0.0);
	void getGrid(GridMode& display, GridMode& quantise, double& domain, double& value) const;
	
	void paint(Graphics& g);
	void paintBackground(Graphics& g);
	void resized();
		
	void mouseMove         (const MouseEvent& e);
    void mouseEnter        (const MouseEvent& e);
	void mouseDown         (const MouseEvent& e);
	void mouseDrag         (const MouseEvent& e);
	void mouseUp           (const MouseEvent& e);
	
	void addListener (EnvelopeComponentListener* const listener);
    void removeListener (EnvelopeComponentListener* const listener);
	void sendChangeMessage();
	
	EnvelopeLegendComponent* getLegend();
	void setLegendText(Text const& legendText);
	void setLegendTextToDefault();
	int getHandleIndex(EnvelopeHandleComponent* handle) const;
	EnvelopeHandleComponent* getHandle(const int index) const;
	
	EnvelopeHandleComponent* getPreviousHandle(const EnvelopeHandleComponent* thisHandle) const;
	EnvelopeHandleComponent* getNextHandle(const EnvelopeHandleComponent* thisHandle) const;
	EnvelopeHandleComponent* addHandle(int newX, int newY, EnvCurve curve);
	EnvelopeHandleComponent* addHandle(double newDomain, double newValue, EnvCurve curve);
	void removeHandle(EnvelopeHandleComponent* thisHandle);
	void quantiseHandle(EnvelopeHandleComponent* thisHandle);
	
	bool isReleaseNode(EnvelopeHandleComponent* thisHandle) const;
	bool isLoopNode(EnvelopeHandleComponent* thisHandle) const;
	void setReleaseNode(const int index);
	void setReleaseNode(EnvelopeHandleComponent* thisHandle);
	int getReleaseNode() const;
	void setLoopNode(const int index);
	void setLoopNode(EnvelopeHandleComponent* thisHandle);
	int getLoopNode() const;
	
	void setAllowCurveEditing(const bool flag);
	bool getAllowCurveEditing() const;
	void setAllowNodeEditing(const bool flag);
	bool getAllowNodeEditing() const;
	
	double convertPixelsToDomain(int pixelsX, int pixelsXMax = -1) const;
	double convertPixelsToValue(int pixelsY, int pixelsYMax = -1) const;
	double convertDomainToPixels(double domainValue) const;
	double convertValueToPixels(double value) const;
	
	Env getEnv() const;
	void setEnv(Env const& env);
	float lookup(const float time) const;
	void setMinMaxNumHandles(int min, int max);
	
	double constrainDomain(double domainToConstrain) const;
	double constrainValue(double valueToConstrain) const;
	
//	double quantiseDomain(double value);
//	double quantiseValue(double value);
	
	enum EnvColours { Node, ReleaseNode, LoopNode, Line, LoopLine, Background, GridLine, LegendText, LegendBackground, NumEnvColours };
	void setEnvColour(const EnvColours which, RGBAColour const& colour) throw();
	const RGBAColour& getEnvColour(const EnvColours which) const throw();
	
	enum MoveMode { MoveClip, MoveSlide, NumMoveModes };
	
private:
	void recalculateHandles();
	
	SortedSet <void*> listeners;
	Array<EnvelopeHandleComponent*> handles;
	int minNumHandles, maxNumHandles;
	double domainMin, domainMax;
	double valueMin, valueMax;
	double valueGrid, domainGrid;
	GridMode gridDisplayMode, gridQuantiseMode;
	EnvelopeHandleComponent* draggingHandle;
	int curvePoints;
	int releaseNode, loopNode;
	
	bool allowCurveEditing:1;
	bool allowNodeEditing:1;
	
	RGBAColour colours[NumEnvColours];
};

class EnvelopeLegendComponent : public Component
{
public:
	EnvelopeLegendComponent(Text const& defaultText = Text::empty);
	virtual ~EnvelopeLegendComponent();
	
	EnvelopeComponent* getEnvelopeComponent() const;
	
	void paint(Graphics& g);
	void resized();
	void setText(Text const& legendText);
	void setText();
	
	virtual double mapValue(double value);
	virtual double mapTime(double time);
	virtual String getValueUnits() { return String::empty; }
	virtual String getTimeUnits() { return String::empty; }
	
private:
	Label* text;
	Text defaultText;
};

/** For displaying and editing a breakpoint envelope with a legend. 
 This provides additional information about the points. 
 @ingoup EnvUGens
 @see Env */
class EnvelopeContainerComponent : public Component
{
public:
	EnvelopeContainerComponent(Text const& defaultText = Text::empty);
	~EnvelopeContainerComponent();
	void resized();
	
	EnvelopeComponent* getEnvelopeComponent() const		{ return envelope; }
	EnvelopeLegendComponent* getLegendComponent() const	{ return legend;   }
	void setLegendComponent(EnvelopeLegendComponent* newLegend);
	
	
	void addListener (EnvelopeComponentListener* const listener) { envelope->addListener(listener); }
    void removeListener (EnvelopeComponentListener* const listener) { envelope->removeListener(listener); }
	
	Env getEnv() const { return getEnvelopeComponent()->getEnv(); }
	void setEnv(Env const& env) { return getEnvelopeComponent()->setEnv(env); }
	float lookup(const float time) const { return getEnvelopeComponent()->lookup(time); }
	
	void setEnvColour(const EnvelopeComponent::EnvColours which, RGBAColour const& colour) throw()
	{
		envelope->setEnvColour(which, colour);
	}
	
	const RGBAColour& getEnvColour(const EnvelopeComponent::EnvColours which) const throw()
	{
		return envelope->getEnvColour(which);
	}
	
	void setDomainRange(const double min, const double max)		{ envelope->setDomainRange(min, max);	}
	void setDomainRange(const double max)						{ setDomainRange(0.0, max);				}
	void getDomainRange(double& min, double& max) const			{ envelope->getDomainRange(min, max);	}
	void setValueRange(const double min, const double max)		{ envelope->setValueRange(min, max);	} 
	void setValueRange(const double max)						{ setValueRange(0.0, max);				}
	void getValueRange(double& min, double& max) const			{ envelope->getValueRange(min, max);	}
	
	void setGrid(const EnvelopeComponent::GridMode display, 
				 const EnvelopeComponent::GridMode quantise, 
				 const double domain = 0.0, 
				 const double value = 0.0)
	{
		envelope->setGrid(display, quantise, domain, value);
	}
	
	void getGrid(EnvelopeComponent::GridMode& display, 
				 EnvelopeComponent::GridMode& quantise,
				 double& domain, 
				 double& value) const
	{
		envelope->getGrid(display, quantise, domain, value);
	}
	
	void setAllowCurveEditing(const bool flag)	{ envelope->setAllowCurveEditing(flag);		}
	bool getAllowCurveEditing() const			{ return envelope->getAllowCurveEditing();	}
	void setAllowNodeEditing(const bool flag)	{ envelope->setAllowNodeEditing(flag);		}
	bool getAllowNodeEditing() const			{ return envelope->getAllowNodeEditing();	}

	
private:
	EnvelopeComponent*			envelope;
	EnvelopeLegendComponent*	legend;
};

class EnvelopeCurvePopup :	public PopupComponent,
							public SliderListener,
							public ComboBoxListener
{
private:
	
	class CurveSlider : public Slider
	{
	public:
		CurveSlider() : Slider(T("CurveSlider")) { }
		const String getTextFromValue (double value)
		{
			value = cubed(value);
			value = linlin(value, -1.0, 1.0, -50.0, 50.0);
			return String(value, 6);
		}
	};
	
	EnvelopeHandleComponent* handle;
	Slider *slider;
	ComboBox *combo;
	
	bool initialised;
	
	static const int idOffset;

	EnvelopeCurvePopup(EnvelopeHandleComponent* handle);
	
public:	
	static void create(EnvelopeHandleComponent* handle, int x, int y);
	
	~EnvelopeCurvePopup();
	void resized();
	void sliderValueChanged(Slider* sliderThatChanged);
	void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
	
};

class EnvelopeNodePopup :	public PopupComponent,
							public ComboBoxListener,
							public ButtonListener
{
private:
	EnvelopeHandleComponent* handle;
	ComboBox *combo;
	TextButton *setLoopButton;
	TextButton *setReleaseButton;
	
	bool initialised;
	
	static const int idOffset;
	
	EnvelopeNodePopup(EnvelopeHandleComponent* handle);
	
public:	
	enum NodeType { Normal, Release, Loop, ReleaseAndLoop };
	
	static void create(EnvelopeHandleComponent* handle, int x, int y);
	
	~EnvelopeNodePopup();
	void resized();
	void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
	void buttonClicked(Button *button);
};

#endif // gpl


#endif //UGEN_JUCEENVELOPECOMPONENT_H