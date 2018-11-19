#pragma once
#include <stdexcept>

namespace OpenPE
{
	// PE Exception class
	class PEException : public std::runtime_error
	{
		public:
			enum PEException_ID
			{
				PEEXCEPTION_UNKNOWN_ERROR,
				PEEXCEPTION_ERROR_READING_FILE,
				PEEXCEPTION_BAD_PE_FILE,
				PEEXCEPTION_BAD_DOS_HEADER,
				PEEXCEPTION_IMAGE_NT_HEADERS_NOT_FOUND,
				PEEXCEPTION_ERROR_READING_IMAGE_NT_HEADERS,
				PEEXCEPTION_ERROR_READING_DATA_DIRECTORIES,
				PEEXCEPTION_INCORRECT_PE_SIGNATURE,
				PEEXCEPTION_INCORRECT_NUMBER_OF_RVAS_AND_SIZES,
				PEEXCEPTION_TOO_MANY_SECTIONS,
				PEEXCEPTION_INCORRECT_SECTION_ALIGNMENT,
				PEEXCEPTION_INCORRECT_FILE_ALIGNMENT,
				PEEXCEPTION_INCORRECT_SIZE_OF_IMAGE,
				PEEXCEPTION_INCORRECT_SIZE_OF_HEADERS,
				PEEXCEPTION_ERROR_READING_DOS_OVERLAY,
				PEEXCEPTION_IMAGE_SECTION_HEADER_NOT_FOUND,
				PEEXCEPTION_IMAGE_SECTION_ERROR_READING_HEADER,
				PEException_IMAGE_SECTION_ZERO_SIZES,
				PEException_IMAGE_SECTION_INCORRECT_ADDRESS_OR_SIZES,
				PEException_IMAGE_SECTION_DATA_NOT_FOUND,
				PEException_IMAGE_SECTION_ERROR_READING_SECTION_DATA,
				PEException_IMAGE_SECTION_TABLE_INCORRECT,

				PEEXCEPTION_DIRECTORY_DOESN_NOT_EXISTS
			};

		public:
			// Constructors
			explicit PEException(const char* pExceptionString, PEException_ID pe_eid = PEException_ID::PEEXCEPTION_UNKNOWN_ERROR);
			explicit PEException(const std::string& pExceptionString, PEException_ID pe_eid = PEException_ID::PEEXCEPTION_UNKNOWN_ERROR);

			// Returns exception id
			PEException_ID	getId() const;

			// Destructor
			virtual ~PEException() throw()
			{};
		private:
			PEException_ID	m_ePEExceptionID;
	};
}