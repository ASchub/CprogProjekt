#pragma once
#include <string>
#include "Labeled.h"

namespace cwing {

	class Label : public Labeled
	{
	public:
		static Label* getInstance(int x, int y, const std::string& txt);
		void draw() const;
		~Label();
	protected:
		Label(int x, int y, const std::string& txt);
	};

} // cwing