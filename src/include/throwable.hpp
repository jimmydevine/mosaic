#pragma once

#include <string>

#define BACKWARD_HAS_BFD 1
#include "backward.hpp"


namespace Mosaic {

	/***********************************************************************************************
	*
	*
	***********************************************************************************************/
	class Throwable {
		private:
			backward::StackTrace st;
			std::string msg;
			std::stringstream msg_stream;


			/***************************************************************************************
			*
			*
			***************************************************************************************/
			std::string get_time() {
				std::string time_str;
				time_t raw_time;
				time(&raw_time);
				time_str = ctime(&raw_time);
				//without the newline character
				return time_str.substr(0 , time_str.size() - 1);
			}


			/***************************************************************************************
			*
			*
			***************************************************************************************/
			std::string get_logline_header() {
				std::stringstream header;
				header.str("");
				header << "[" << this->get_time() << "] ";
				return header.str();
			}


			/***************************************************************************************
			*
			*
			***************************************************************************************/
			void write_impl() {
				this->msg = this->msg_stream.str();
			}


			/***************************************************************************************
			*
			*
			***************************************************************************************/
			template <typename First, typename...Rest> void write_impl(First parm1, Rest...parm) {
				this->msg_stream<<parm1;
				this->write_impl(parm...);
			}


		public:


			/***************************************************************************************
			*
			*
			***************************************************************************************/
			Throwable() {
				this->st.load_here(32);
			}


			Throwable(const Throwable &t) {
				this->st = t.st;
				this->msg = t.msg;
			}


			/***************************************************************************************
			*
			*
			***************************************************************************************/
			template <typename...Args> Throwable write(Args...args) {
				this->write_impl(args...);
				return *this;
			}


			/***************************************************************************************
			*
			*
			***************************************************************************************/
			~Throwable() {
			}

			void display() {
								this->st.skip_n_firsts(3);
				backward::Printer p;
				p.object = true;
				p.color_mode = backward::ColorMode::always;
				p.address = true;
				p.print(this->st, stdout);
								std::cout << "\033[1;31mException Thrown: " << this->msg << "\033[0m" << std::endl;
			}


			std::string getMessage() {
				return this->msg;
			}
	};


}

