// $Id: ugen_Random.h 358 2012-05-10 06:38:11Z 0x4d52 $
// $HeadURL: http://ugen.googlecode.com/svn/trunk/UGen/core/ugen_Random.h $

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

#ifndef _UGEN_ugen_Random_H_
#define _UGEN_ugen_Random_H_

#include "../basics/ugen_InlineUnaryOps.h"
#include "../basics/ugen_InlineBinaryOps.h"

#ifndef UGEN_NOEXTGPL

class Ran088 
{
public:
	
	/// @name Construction and destruction
	/// @{
	
	Ran088(unsigned int seed) throw();
	static Ran088& defaultGenerator() throw()
	{
		static Ran088 r(0);
		return r;
	}
	
	/// @} <!-- end Construction and destruction ---------------- -->
	
	
	
	/// @name Random values from external states
	/// @{
	
	void setSeed(unsigned int seed) throw();
	
	void get(unsigned int& s1, unsigned int& s2, unsigned int& s3) throw();
	void set(unsigned int s1, unsigned int s2, unsigned int s3) throw();
	
	static unsigned int next( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw();
	static double nextDouble( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw();
	static float nextFloat( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw();
	static float nextFloat0( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw();
	static float nextBiFloat( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw();
	static float nextFloat8( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw();
	static float coin( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw();
	
	/// @} <!-- end Random values from external states ------------------------------ -->
	
	/// @name Random values from internal state
	/// @{
	
	unsigned int next() throw();
	int nextInt(int scale) throw();
	int nextBiInt(int scale) throw();
	int nextLinearInt(int scale) throw();
	int nextBiLinearInt(int scale) throw();
	
	float coin() throw();
	float nextFloat() throw();
	float nextBiFloat() throw();
	float nextFloat0() throw();
	float nextFloat8() throw();
	double nextDouble() throw();
	double nextDouble(double scale) throw();
	double nextBiDouble(double scale) throw();
	double nextLinearDouble(double scale) throw();
	double nextBiLinearDouble(double scale) throw();
	double nextExpRandRange(double lo, double hi) throw();
	double nextExpRand(double scale) throw();
	double nextBiExpRand(double scale) throw();
	double nextGaussianApprox(double scale) throw();
	
	inline double operator() (double scale)  throw() { return nextDouble(scale); }
	inline double operator() (double lo, double hi) throw() { return nextDouble(hi-lo)+lo; }
	
	inline int next(int lo, int hi) throw() { return nextInt(hi-lo)+lo; }
	inline float next(float lo, float hi) throw() { return nextFloat() * (hi-lo) + lo; }
	inline double next(double lo, double hi) throw() { return nextDouble() * (hi-lo) + lo; }
	
	inline int nextExp(int lo, int hi) throw() { return int(nextExpRandRange((double)lo, (double)hi)+0.5); }
	inline float nextExp(float lo, float hi) throw() { return (float)nextExpRandRange((double)lo, (double)hi); }
	inline double nextExp(double lo, double hi) throw() { return nextExpRandRange(lo, hi); }
	
	inline int nextLin(int lo, int hi) throw() { return nextLinearInt(hi-lo)+lo; }
	inline float nextLin(float lo, float hi) throw() { return (float)nextLinearDouble((double)(hi-lo)) + lo; }
	inline double nextLin(double lo, double hi) throw() { return nextLinearDouble(hi-lo) + lo;  }
	
	
	/// @} <!-- end Random values from internal state ------------------------------ -->
	
	
	
private:
	unsigned int s1, s2, s3;		// random generator state
	
	// using the copy and assignment operators might lead to unexpected results, 
	// especially copying the default generator,
	// if you're getting an error here is might because you've done this:
	// Ran088 rand = Ran088::defaultGenerator();
	// instead of:
	// Ran088& rand = Ran088::defaultGenerator();
	// if you really wqnt two or more Ran088 with the same state use get() and set()
	Ran088(Ran088 const& copy);
	Ran088& operator= (Ran088 const& other);
};

inline double rand(double scale) throw()
{
	return Ran088::defaultGenerator().nextDouble(scale);
}

inline double rand(double lo, double hi) throw()
{
	return Ran088::defaultGenerator().nextDouble(hi-lo)+lo;
}

inline double rand2(double scale) throw()
{
	return Ran088::defaultGenerator().nextBiDouble(scale);
}

inline double exprand(double lo, double hi) throw()
{
	return Ran088::defaultGenerator().nextExpRandRange(lo, hi);
}

inline float rand(float scale) throw()
{
	return (float)(Ran088::defaultGenerator().nextDouble(scale));
}

inline float rand(float lo, float hi) throw()
{
	return (float)(Ran088::defaultGenerator().nextDouble(hi-lo)+lo);
}

inline float rand2(float scale) throw()
{
	return (float)(Ran088::defaultGenerator().nextBiDouble(scale));
}

inline float exprand(float lo, float hi) throw()
{
	return (float)(Ran088::defaultGenerator().nextExpRandRange(lo, hi));
}

inline int rand(int scale) throw()
{
	return (int)(Ran088::defaultGenerator().nextInt(scale));
}

inline int rand(int lo, int hi) throw()
{
	return (int)(Ran088::defaultGenerator().nextInt(hi-lo)+lo);
}

inline int rand2(int scale) throw()
{
	return (int)(Ran088::defaultGenerator().nextBiInt(scale));
}

inline double exprand(int lo, int hi) throw()
{
	return Ran088::defaultGenerator().nextExpRandRange(lo, hi);
}


inline Ran088::Ran088(unsigned int seed) throw()
{		
	setSeed(seed);
}

inline void Ran088::setSeed(unsigned int seed) throw()
{
	int* seedPtr = 0;
	
	if(seed == 0)
	{
		// use the addess of an allocated pointer as the seed
		seedPtr = new int;
		seed = (unsigned int)(unsigned long)seedPtr;
		seed *= 39458953U;
		seed += 18479161U;
	}
	
	// initialize seeds using the given seed value taking care of
	// the requirements. The constants below are arbitrary otherwise
	s1 = 1243598713U ^ seed; if (s1 <  2) s1 = 1243598713U;
	s2 = 3093459404U ^ seed; if (s2 <  8) s2 = 3093459404U;
	s3 = 1821928721U ^ seed; if (s3 < 16) s3 = 1821928721U;	
	
	delete seedPtr;	
}

inline void Ran088::get(unsigned int& s1, unsigned int& s2, unsigned int& s3) throw()
{
	s1 = this->s1;
	s2 = this->s2;
	s3 = this->s3;
}

inline void Ran088::set(unsigned int s1, unsigned int s2, unsigned int s3) throw()
{
	this->s1 = s1;
	this->s2 = s2;
	this->s3 = s3;
}

inline unsigned int Ran088::next() throw()
{
	// generate a random 32 bit number
	s1 = ((s1 &  -2) << 12) ^ (((s1 << 13) ^  s1) >> 19);
	s2 = ((s2 &  -8) <<  4) ^ (((s2 <<  2) ^  s2) >> 25);
	s3 = ((s3 & -16) << 17) ^ (((s3 <<  3) ^  s3) >> 11);
	return s1 ^ s2 ^ s3;
}

inline double Ran088::nextDouble() throw()
{
	// return a double from 0.0 to 0.999...
#if BYTE_ORDER == BIG_ENDIAN
	union { struct { unsigned int hi, lo; } i; double f; } du;
#else
	union { struct { unsigned int lo, hi; } i; double f; } du;
#endif
	du.i.hi = 0x41300000; 
	du.i.lo = next();
	return du.f - 1048576.;
}

inline double Ran088::nextDouble(double scale) throw()
{
	return Ran088::defaultGenerator().nextDouble() * scale;
}

inline double Ran088::nextBiDouble(double scale) throw()
{
	return Ran088::defaultGenerator().nextDouble() * scale * 2.0 - scale;
}

inline float Ran088::nextFloat() throw()
{
	// return a float from 0.0 to 0.999...
	union { unsigned int i; float f; } u;		// union for floating point conversion of result
	u.i = 0x3F800000 | (next() >> 9);
	return u.f - 1.f;
}

inline float Ran088::nextFloat0() throw()
{
	// return a float from +1.0 to +1.999...
	union { unsigned int i; float f; } u;		// union for floating point conversion of result
	u.i = 0x3F800000 | (next() >> 9);
	return u.f;
}

inline float Ran088::nextBiFloat() throw()
{
	// return a float from -1.0 to +0.999...
	union { unsigned int i; float f; } u;		// union for floating point conversion of result
	u.i = 0x40000000 | (next() >> 9);
	return u.f - 3.f;
}

inline float Ran088::nextFloat8() throw()
{
	// return a float from -0.125 to +0.124999...
	union { unsigned int i; float f; } u;		// union for floating point conversion of result
	u.i = 0x3E800000 | (next() >> 9);
	return u.f - 0.375f;
}

inline float Ran088::coin() throw()
{
	// only return one of the two values -1.0 or +1.0
	union { unsigned int i; float f; } u;		// union for floating point conversion of result
	u.i = 0x3F800000 | (0x80000000 & next());
	return u.f;
}

#ifndef UGEN_ANDROID
inline int Ran088::nextInt(int scale) throw()
{
	// return an int from 0 to scale - 1
	return (int)std::floor(scale * nextDouble());
}

inline int Ran088::nextBiInt(int scale) throw()
{
	// return a int from -scale to +scale
	return (int)std::floor((2. * scale + 1.) * nextDouble() - scale);
}
#else
// android
inline int Ran088::nextInt(int scale) throw()
{
	// return an int from 0 to scale - 1
	return (int)floor(scale * nextDouble());
}

inline int Ran088::nextBiInt(int scale) throw()
{
	// return a int from -scale to +scale
	return (int)floor((2. * scale + 1.) * nextDouble() - scale);
}
#endif

inline int Ran088::nextLinearInt(int scale) throw()
{
	int a = nextInt(scale);
	int b = nextInt(scale);
	return min(a,b);
}

inline double Ran088::nextLinearDouble(double scale) throw()
{
	double a = nextDouble();
	double b = nextDouble();
	return min(a,b) * scale;
}

inline int Ran088::nextBiLinearInt(int scale) throw()
{
	int a = nextInt(scale);
	int b = nextInt(scale);
	return a - b;
}

inline double Ran088::nextBiLinearDouble(double scale) throw()
{
	double a = nextDouble();
	double b = nextDouble();
	return (a - b) * scale;
}

#ifndef UGEN_ANDROID
inline double Ran088::nextExpRandRange(double lo, double hi) throw()
{
	return lo * std::exp(std::log(hi / lo) * nextDouble());
}

inline double Ran088::nextExpRand(double scale) throw()
{
	double z;
	while ((z = nextDouble()) == 0.0) {}
	return -std::log(z) * scale;
}
#else
inline double Ran088::nextExpRandRange(double lo, double hi) throw()
{
	return lo * exp(log(hi / lo) * nextDouble());
}

inline double Ran088::nextExpRand(double scale) throw()
{
	double z;
	while ((z = nextDouble()) == 0.0) {}
	return -log(z) * scale;
}
#endif

//inline double Ran088::nextBiExpRand(double scale)
//{
//	double z;
//	while ((z = drand2(1.)) == 0.0 || z == -1.0) {}
//	if (z > 0.0) z = std::log(z);
//	else z = -std::log(-z);
//	return z * scale;
//}

inline double Ran088::nextGaussianApprox(double scale) throw()
{
	// larry polansky's poor man's gaussian generator
	return (nextDouble() + nextDouble() + nextDouble() - 1.5) * 0.666666667 * scale;
}

inline unsigned int Ran088::next( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw()
{
	s1 = ((s1 &  -2) << 12) ^ (((s1 << 13) ^  s1) >> 19);
	s2 = ((s2 &  -8) <<  4) ^ (((s2 <<  2) ^  s2) >> 25);
	s3 = ((s3 & -16) << 17) ^ (((s3 <<  3) ^  s3) >> 11);
	return s1 ^ s2 ^ s3;
}

inline double Ran088::nextDouble( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw()
{
	union { struct { unsigned int hi, lo; } i; double f; } u;
	u.i.hi = 0x41300000; 
	u.i.lo = next(s1,s2,s3);
	return u.f - 1048576.;
}

inline float Ran088::nextFloat( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw()
{
	// return a float from 0.0 to 0.999...
	union { unsigned int i; float f; } u;
	u.i = 0x3F800000 | (next(s1,s2,s3) >> 9);
	return u.f - 1.f;
}

inline float Ran088::nextFloat0( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw()
{
	// return a float from +1.0 to +1.999...
	union { unsigned int i; float f; } u;
	u.i = 0x3F800000 | (next(s1,s2,s3) >> 9);
	return u.f;
}

inline float Ran088::nextBiFloat( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw()
{
	// return a float from -1.0 to +0.999...
	union { unsigned int i; float f; } u;
	u.i = 0x40000000 | (next(s1,s2,s3) >> 9);
	return u.f - 3.f;
}

inline float Ran088::nextFloat8( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw()
{
	// return a float from -0.125 to +0.124999...
	union { unsigned int i; float f; } u;
	u.i = 0x3E800000 | (next(s1,s2,s3) >> 9);
	return u.f - 0.375f;
}

inline float Ran088::coin( unsigned int& s1, unsigned int& s2, unsigned int& s3 ) throw()
{
	// only return one of the two values -1.0 or +1.0
	union { unsigned int i; float f; } u;
	u.i = 0x3F800000 | (0x80000000 & next(s1,s2,s3));
	return u.f;
}

#else
class Ran088
{
	// fixme:  to allow headers to compile for now
};
#endif // gpl



#endif // _UGEN_ugen_Random_H_
