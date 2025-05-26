#pragma once

// this file is used to define the Base class for the SiaRift framework.
// included in every "header file" that needs to use the Base class.
// Is Singleton class, no copy constructor, no move constructor, no destructor.

namespace SiaRift {
	class Base
	{
	public:
		Base();
		virtual ~Base();
		// Singleton pattern
		Base(const Base&) = delete; // no copy constructor
		Base(Base&&) = delete;      // no move constructor
		Base& operator=(const Base&) = delete; // no copy assignment operator
		Base& operator=(Base&&) = delete; // no move assignment operator


	};
}

