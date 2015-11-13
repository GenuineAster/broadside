#include <fstream>
#include <iostream>
#include <iomanip>
#include <exception>
#include <vector>

/* 
 * Basic, outdated and mostly broken resource for parsing .forge files can be found here:
 * http://www.fluffy-demons.net/index.php?title=.forge_file_format
 */

// Add values labelled `unused` are not actually unused, but their use is unknown
namespace Scimitar
{
	struct [[gnu::packed]] HeaderChunk {
		char scimitar[9];
		uint32_t version;
		uint32_t index_header_ptr;
		uint32_t unused0[4];
		char unused1[1017];
	};

	struct [[gnu::packed]] IndexHeaderChunk {
		uint32_t record_count;
		uint32_t unused0[10];
		uint32_t record_count_copy;
		uint32_t unused1[7];
		uint32_t index_chunk_2_ptr;
		uint32_t unused2[1];
		uint32_t fp_chunk_ptr;
		uint32_t unused3[1];
		uint32_t file_entry_chunk_ptr;
		uint32_t unused4[4];
	};

	struct [[gnu::packed]] FPChunk {
		char a[];
	};

	struct [[gnu::packed]] FileRecord {
		uint32_t resource_ptr;
		uint32_t unused0[4];
	};

	struct [[gnu::packed]] FileDescription {
		uint32_t file_size;
		uint32_t unused0[6];
		uint32_t next_index;
		uint32_t prev_index;
		uint32_t unused1[1];
		uint32_t timestamp;
		char name[128];
		uint32_t unused2[5];
	};
}

int main(int argc, char **argv) {
	if (argc < 2)  {
		throw std::runtime_error("Invalid number of arguments.");
	}
	std::cout << "Opening file " << argv[1] << std::endl;

	std::string filename = argv[1];
	std::ifstream file(filename, std::ios::binary);

	Scimitar::HeaderChunk hdr_chunk;
	file.read(reinterpret_cast<char*>(&hdr_chunk), sizeof(hdr_chunk));

	Scimitar::IndexHeaderChunk idx_hdr_chunk;
	file.read(reinterpret_cast<char*>(&idx_hdr_chunk), sizeof(idx_hdr_chunk));

	std::vector<Scimitar::FileRecord> file_records(idx_hdr_chunk.record_count);
	for (auto &file_record : file_records) {
		file.read(reinterpret_cast<char*>(&file_record), sizeof(file_record));
	}

	file.seekg(idx_hdr_chunk.index_chunk_2_ptr);

	std::vector<Scimitar::FileDescription> file_descs(idx_hdr_chunk.record_count);
	for (auto &file_desc : file_descs) {
		file.read(reinterpret_cast<char*>(&file_desc), sizeof(Scimitar::FileDescription));
	}

	// print ALL THE DATA

	std::cout<<std::setfill('0');
	std::cout<<"Size of Scimitar Header Chunk:        0x"<<std::setw(16)<<std::hex<<sizeof(Scimitar::FileDescription)<<std::endl;
	std::cout<<"Size of Index Header Chunk:           0x"<<std::setw(16)<<std::hex<<sizeof(Scimitar::IndexHeaderChunk)<<std::endl;
	std::cout<<"Size of File Record Chunk:            0x"<<std::setw(16)<<std::hex<<sizeof(Scimitar::FileRecord)<<std::endl;
	std::cout<<"Size of File Description Chunk:       0x"<<std::setw(16)<<std::hex<<sizeof(Scimitar::FileDescription)<<std::endl;
	std::cout<<"Scimitar identifier:                  "<<hdr_chunk.scimitar<<std::endl;
	std::cout<<"Number of file records:               0x"<<std::setw(16)<<std::hex<<idx_hdr_chunk.record_count<<std::endl;
	std::cout<<"Position of 2nd Index Chunk:          0x"<<std::setw(16)<<std::hex<<idx_hdr_chunk.index_chunk_2_ptr<<std::endl;
	std::cout<<"Position of FP Chunk:                 0x"<<std::setw(16)<<std::hex<<idx_hdr_chunk.fp_chunk_ptr<<std::endl;
	std::cout<<"Position of File Entry Chunk:         0x"<<std::setw(16)<<std::hex<<idx_hdr_chunk.file_entry_chunk_ptr<<std::endl;

	std::cout<<hdr_chunk.unused0[0]<<std::endl;
	std::cout<<hdr_chunk.unused0[1]<<std::endl;
	std::cout<<hdr_chunk.unused0[2]<<std::endl;
	std::cout<<hdr_chunk.unused0[3]<<std::endl;

	std::cout<<idx_hdr_chunk.unused0[0]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[1]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[2]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[3]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[4]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[5]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[6]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[7]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[8]<<std::endl;
	std::cout<<idx_hdr_chunk.unused0[9]<<std::endl;

	std::cout<<idx_hdr_chunk.unused1[1]<<std::endl;
	std::cout<<idx_hdr_chunk.unused1[2]<<std::endl;
	std::cout<<idx_hdr_chunk.unused1[3]<<std::endl;
	std::cout<<idx_hdr_chunk.unused1[4]<<std::endl;
	std::cout<<idx_hdr_chunk.unused1[5]<<std::endl;
	std::cout<<idx_hdr_chunk.unused1[6]<<std::endl;

	std::cout<<idx_hdr_chunk.unused2[0]<<std::endl;

	std::cout<<idx_hdr_chunk.unused3[0]<<std::endl;

	std::cout<<idx_hdr_chunk.unused4[0]<<std::endl;
	std::cout<<idx_hdr_chunk.unused4[1]<<std::endl;
	std::cout<<idx_hdr_chunk.unused4[2]<<std::endl;
	std::cout<<idx_hdr_chunk.unused4[3]<<std::endl;

	for (auto n = 0; n < file_records.size(); ++n) {
	// for (auto n = 0; n < 3; ++n) {
		std::cout<<file_descs[n].name<<std::endl;
		std::cout<<file_descs[n].file_size<<std::endl;
		std::cout<<file_records[n].resource_ptr<<std::endl;
		std::cout<<file_descs[n].next_index<<std::endl;
		std::cout<<file_descs[n].prev_index<<std::endl;
		std::cout<<file_records[n].unused0[0]<<std::endl;
		std::cout<<file_records[n].unused0[1]<<std::endl;
		std::cout<<file_records[n].unused0[2]<<std::endl;
		std::cout<<file_records[n].unused0[3]<<std::endl;
		std::cout<<file_descs[n].unused0[0]<<std::endl;
		std::cout<<file_descs[n].unused0[1]<<std::endl;
		std::cout<<file_descs[n].unused0[2]<<std::endl;
		std::cout<<file_descs[n].unused0[3]<<std::endl;
		std::cout<<file_descs[n].unused0[4]<<std::endl;
		std::cout<<file_descs[n].unused0[5]<<std::endl;
		std::cout<<file_descs[n].unused1[0]<<std::endl;
		std::cout<<file_descs[n].unused2[0]<<std::endl;
		std::cout<<file_descs[n].unused2[1]<<std::endl;
		std::cout<<file_descs[n].unused2[2]<<std::endl;
		std::cout<<file_descs[n].unused2[3]<<std::endl;
		std::cout<<file_descs[n].unused2[4]<<std::endl;
	}
}


// 2e1aa7


