#pragma once

#include <istream>					// for 'std::istream'
#include "OpenPEStructures.h"		// for PE all related structures.
#include "OpenPEIProperties.h"		// IProperties interface
#include "OpenPESection.h"

namespace OpenPE
{
	class PEBase
	{
		public:
			// Constructor
			PEBase(std::istream& pFileStream, const PEIProperties& pProperties, bool bReadDebugRawData = true);

			PEBase(const PEBase& pe);
			PEBase& operator=(const PEBase& pe);
		public:
			// Destructor
			~PEBase();
		public:
			// Directories

			// Returns 'true' if Directory exists
			bool					directoryExists(uint32_t iDirectoryID) const;
			// Removes specified Directory
			void					removeDirectory(uint32_t iDirectoryID);

			// Returns Directory RVA
			uint32_t				getDirectoryRVA(uint32_t iDirectoryID) const;
			// Returns Directory Size
			uint32_t				getDirectorySize(uint32_t iDirectoryID) const;

			// Sets Directory RVA (just a value in PE Header, no movement occurs)
			void					setDirectoryRVA(uint32_t iDirectoryID, uint32_t iRVA);
			// Sets Directory Size (just a value in PE Header, no movement occurs)
			void					setDirectorySize(uint32_t iDirectoryID, uint32_t iRVA);

			// Returns 'true' if Image has Import Directory
			bool					hasImports() const;
			// Returns 'true' if Image has Export Directory
			bool					hasExports() const;
			// Returns 'true' if Image has Resources Directory
			bool					hasResources() const;
			// Returns 'true' if Image has Security Directory
			bool					hasSecurity() const;
			// Returns 'true' if Image has Relocations
			bool					hasReloc() const;
			// Returns 'true' if Image has TLS Directory
			bool					hasTLS() const;
			// Returns 'true' if Image has Config Directory
			bool					hasConfig() const;
			// Returns 'true' if Image has Bound Import Directory
			bool					hasBoundImport() const;
			// Returns 'true' if Image has Delayed Import Directory
			bool					hasDelayImport() const;
			// Returns 'true' if Image has COM Directory
			bool					isDotNet() const;
			// Returns 'true' if Image has Exception Directory
			bool					hasExceptionDirectory() const;
			// Returns 'true' if Image has Debug Directory
			bool					hasDebug() const;

			// Returns Subsystem
			uint16_t				getSubsystem() const;
			// Sets Subsystem value
			void					setSubsystem(uint16_t iSubsystem);

			// Returns true if image has console subsystem
			bool					isConsole() const;
			// Returns true if image has GUI subsystem
			bool					isGui() const;
	public:
			// PE Headers

			// Returns NT Headers Data Pointer
			virtual char*			getNTHeadersPtr() const;

			// Returns sizeof() NT Headers
			uint32_t				get_sizeofNTHeader() const;
			// Returns sizeof() Optional Header
			uint32_t				get_sizeOfOptionalHeader() const;

			// Returns Size of Headers
			uint32_t				getSizeOfHeaders() const;
			// Returns Size of Optional Header
			uint32_t				getSizeOfOptionalHeader() const;

			// Return the PE Signature
			uint32_t				getPESignature() const;

			// Returns number of RVA's & Sizes (number of DATA_DIRECTORY entries)
			uint32_t				getNumberOfRVAsAndSizes() const;
			// Sets number of RVA's & Sizes (number of DATA_DIRECTORY entries)
			void					setNumberOfRVAsAndSizes(uint32_t iNumberOfRVAsAndSizes);

			// Returns PE characteristics
			uint16_t				getCharacteristics() const;

			// Returns Checksum of PE file from Header
			uint32_t				getChecksum() const;
			// Sets Checksum of PE file
			void					setChecksum(uint32_t iChecksum);

			// Returns Number of Sections
			uint32_t				getNumberOfSections() const;

			uint16_t				getPEMagic() const;
			uint16_t				getNeededMagic() const;

			// Returns Section alignment
			virtual uint32_t		getSectionAlignment() const;
			// Returns File alignment
			virtual uint32_t		getFileAlignment() const;

			// Returns Size of the Image
			virtual uint32_t		getSizeOfImage() const;

			// Returns Image Entry Point
			uint32_t				getEntryPoint() const;
			// Sets Image Entry Point (Just the value in PE Header)
			void					setEntryPoint(uint32_t iNewEntryPoint);

			// Returns Image base for PE(32-bit) & PE+(64-bit) respectively
			uint32_t				getImageBase32() const;
			uint64_t				getImageBase64() const;
		public:
			// Image

			// Returns the PE type (PE or PE+) from PEType enumeration of this Image
			static PEType			getPEType(std::istream& pFileStream);
			PEType					getPEType() const;
			
			// Returns true if Image has an Overlay
			bool					hasOverlay() const;
		private:
			static const uint32_t	MAXIMUM_NUMBER_OF_SECTIONS = 0x60;
			static const uint32_t	MINIMUM_FILE_ALIGNMENT = 512;
		private:
			// Reads & checks DOS headers from istream
			void					readDOSHeader(std::istream& pFileStream);
		public:
			// Reads & checks DOS headers from istream
			static void				readDOSHeader(std::istream& pFileStream, Image_Dos& _dosHeader);

			// Reads & checks PE Headers/Sections/Data
			void					readPE(std::istream& pFileStream, bool bReadDebugRawData);
	private:
			// 
			Image_Dos				m_DOSHeader;

			// Rich (stub) overlay data (for MSVS)
			std::string				m_sRichOverlay;

			// List of Image Sections
			SECTION_LIST			m_vSections;

			// True if Image has an Overlay
			bool					m_bHasOverlay;

			// Raw SizeOfHeader - sized Data from the beginning of Image
			std::string				m_sFullHeadersData;

			PEIProperties*			m_pProperties;
	};
}