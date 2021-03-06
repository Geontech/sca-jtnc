/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of SCA-JTNC core.
 * 
 * SCA-JTNC core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */


#ifndef SCA_CONCURRENT_H
#define SCA_CONCURRENT_H

#include <string>
#include <vector>
#include <sched.h>

#ifdef HAVE_BOOST
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#define _MUTEX                boost::mutex
#define _ULOCK                boost::unique_lock
#define _SLOCK                boost::mutex::scoped_lock

#endif

#ifndef HAVE_BOOST           // resolve with pthreads
#define _MUTEX                
#define _ULOCK                
#define _SLOCK                
#endif

namespace sca {

  typedef   _MUTEX                    Mutex;

  typedef   _ULOCK< Mutex >           ULock;

  typedef   _SLOCK                    ScopedLock;

#define  SCOPED_LOCK(x)               REDHAWK_CPP_NAMESPACE::ScopedLock  __slock(x)

};

#endif
