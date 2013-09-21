/*

 Created by: cgpsmapper
  
 This is open source software. Source code is under the GNU General Public License version 3.0 (GPLv3) license.

 Permission to modify the code and to distribute modified code is granted,
 provided the above notices are retained, and a notice that the code was
 modified is included with the above copyright notice.

*/
#ifndef __IMG_MANAGER
#define __IMG_MANAGER

#include <string>
#include <stdio.h>
#include "global_const.h"

#pragma warning (disable: 1786) 

//klasy do zarz�dzania plikami LBL,RGN,TRE,NET,NOD - 
//czytaj� nag��wek i potrafi� zmieni� po�o�enie danych - przebudowa� plik

//1. Odczytanie pliku danych (mo�e by� podane jako jeden wsp�lny IMG z podaniem pocz�tku, ko�ca i typu)
//2. Zczytanie nag��wka
//3. Modyfikacja nag��wka - pocz�tku danych z automatycznym przesuwaniem pozosta�ych sekcji - tak aby zachowa�
//   domy�ln� kolejno��.
//	 W najprotszym przypadku sprowadza� si� to b�dzie do modyfikacji tylko startu pierwszej sekcji - reszta zostanie
//   automatycznie przesuni�ta

#pragma pack(1)

class img_manager {
protected:
	std::string			main_file;
	unsigned int		file_offset;
	internal_file_type	file_type;
	unsigned char		xor_file;
	unsigned int		internal_size;

	FILE*				input_file;
	FILE*				output_file;
	unsigned short		header_size;

	//sekcja danych
	unsigned char		const_header[0x15];

	//offset do nag��wka - liczony od pocz�tku output_file
	unsigned int		header_offset;

	//offset do pierwszej sekcji danych - liczony od pocz�tku output_file
	unsigned int		data_offset;
	unsigned int		end_data_offset;

public:
	//g�owny IMG
	//offset do pliku
	//typ - jako string: LBL, NET etc..
	img_manager(std::string _main_file,unsigned int _file_offset,internal_file_type _file_type,unsigned char _xor_file,unsigned int _internal_size);
	~img_manager();

	size_t read_data(unsigned char* buffer,int size);
	virtual void	read_const_part();
	virtual void	write_const_part();
	virtual void	read_header();


	void			set_output_file(FILE* _output_file);
	virtual void	set_header_offset(unsigned int _offset);
	virtual unsigned int get_header_end();
	virtual unsigned int get_header_size();
	unsigned int	get_header_begin() {return header_offset;};

	virtual void	set_data_start_offset(unsigned int _offset);
	virtual unsigned int get_data_end_offset();
	virtual unsigned int get_data_size();

	virtual void	write_header();
	virtual void	write_data();
};

class rgn_manager : public img_manager {
protected:
	struct t_rgn_header {
	unsigned int	rgn1_start;
	unsigned int	rgn1_len;

	unsigned int	rgn2_start;
	unsigned int	rgn2_len;
	unsigned char	rgn2_data[20];
	
	unsigned int	rgn3_start;
	unsigned int	rgn3_len;
	unsigned char	rgn3_data[20];

	unsigned int	rgn4_start;
	unsigned int	rgn4_len;
	unsigned char	rgn4_data[20];

	unsigned int	rgn5_start;
	unsigned int	rgn5_len;
	unsigned char	rgn5_data[4];
	} rgn_header;
public:
	rgn_manager(std::string _main_file,unsigned int _file_offset,internal_file_type _file_type,unsigned char _xor_file,unsigned int _internal_size)
		: img_manager(_main_file,_file_offset,_file_type,_xor_file,_internal_size) {};
	
	virtual void	set_data_start_offset(unsigned int _offset);
	virtual void	read_header();
	virtual void	write_header();
};

class lbl_manager : public img_manager {
protected:
	struct t_lbl_header {
	unsigned int	lbl1_start;
	unsigned int	lbl1_len;
	unsigned char	lbl1_data[2];

	unsigned int	lbl2_start;
	unsigned int	lbl2_len;
	unsigned char	lbl2_data[6];

	unsigned int	lbl3_start;
	unsigned int	lbl3_len;
	unsigned char	lbl3_data[6];

	unsigned int	lbl4_start;
	unsigned int	lbl4_len;
	unsigned char	lbl4_data[6];

	unsigned int	lbl5_start;
	unsigned int	lbl5_len;
	unsigned char	lbl5_data[6];

	unsigned int	lbl6_start;
	unsigned int	lbl6_len;
	unsigned char	lbl6_data[5];

	unsigned int	lbl7_start;
	unsigned int	lbl7_len;
	unsigned char	lbl7_data[6];

	unsigned int	lbl8_start;
	unsigned int	lbl8_len;
	unsigned char	lbl8_data[6];

	unsigned int	lbl9_start;
	unsigned int	lbl9_len;
	unsigned char	lbl9_data[6];

	unsigned int	lbl10_start;
	unsigned int	lbl10_len;
	unsigned char	lbl10_data[6];

	unsigned int	lbl11_start;
	unsigned int	lbl11_len;
	unsigned char	lbl11_data[6];

	unsigned char	lbl12_data[6];

	unsigned int	lbl13_start;
	unsigned int	lbl13_len;

	unsigned int	lbl14_start;
	unsigned int	lbl14_len;
	unsigned char	lbl14_data[4];

	unsigned int	lbl15_start;
	unsigned int	lbl15_len;
	unsigned char	lbl15_data[4];

	unsigned int	lbl16_start;
	unsigned int	lbl16_len;
	unsigned char	lbl16_data[6];

	unsigned int	lbl17_start;
	unsigned int	lbl17_len;
	unsigned char	lbl17_data[6];
	} lbl_header;
public:
	lbl_manager(std::string _main_file,unsigned int _file_offset,internal_file_type _file_type,unsigned char _xor_file,unsigned int _internal_size)
		: img_manager(_main_file,_file_offset,_file_type,_xor_file,_internal_size) {};
	
	virtual void	set_data_start_offset(unsigned int _offset);
	virtual void	read_header();
	virtual void	write_header();
};

class tre_manager : public img_manager {
protected:
	struct t_tre_header {
	unsigned int	tre1_start;
	unsigned int	tre1_len;

	unsigned int	tre2_start;
	unsigned int	tre2_len;
	
	unsigned int	tre3_start;
	unsigned int	tre3_len; 
	unsigned char	tre3_data[17];//0x39 - start, 4a - koniec

	unsigned int	tre4_start;
	unsigned int	tre4_len;
	unsigned char	tre4_data[6];

	unsigned int	tre5_start;
	unsigned int	tre5_len;
	unsigned char	tre5_data[6];

	unsigned int	tre6_start;
	unsigned int	tre6_len;
	unsigned char	tre6_data[6];

	unsigned char	tre_ui_data[8];

	unsigned int	tre8_start;
	unsigned int	tre8_len;
	unsigned char	tre8_data[6];

	unsigned int	tre9_start;
	unsigned int	tre9_len;
	unsigned char	tre9_data[8];

	//0x9a - ae
	unsigned char	tre_lock_data[20];
	
	unsigned int	tre10_start;
	unsigned int	tre10_len;
	unsigned int	tre10_data[6];//

	} tre_header;

	unsigned char	tre_const_header[0x21];
	unsigned int	tre_copyright_len;
	unsigned char	tre_copyright_strings[1024];
public:
	tre_manager(std::string _main_file,unsigned int _file_offset,internal_file_type _file_type,unsigned char _xor_file,unsigned int _internal_size)
		: img_manager(_main_file,_file_offset,_file_type,_xor_file,_internal_size) {};
	
	virtual void	write_const_part();
	virtual void	read_const_part();
	virtual void	read_header();

	virtual void	set_data_start_offset(unsigned int _offset);
	virtual unsigned int get_header_end();
	virtual unsigned int get_header_size();
	virtual unsigned int get_data_size();

	virtual void	write_header();
};

class net_manager : public img_manager {
protected:
	struct t_net_header {
	unsigned int	net1_start;
	unsigned int	net1_len;
	unsigned char	net1_net;

	unsigned int	net2_start;
	unsigned int	net2_len;
	unsigned char	net2_net;

	unsigned int	net3_start;
	unsigned int	net3_len;
	unsigned char	net3_net;

	unsigned int	net4_start;
	unsigned short	net4_net1;
	unsigned char	net4_net2;

	unsigned char	net_data[1024];
	} net_header;
public:
	net_manager(std::string _main_file,unsigned int _file_offset,internal_file_type _file_type,unsigned char _xor_file,unsigned int _internal_size)
		: img_manager(_main_file,_file_offset,_file_type,_xor_file,_internal_size) {};
	
	virtual void	read_header();

	virtual void	set_data_start_offset(unsigned int _offset);
	virtual void	write_header();
};

class nod_manager : public img_manager {
protected:
	struct t_nod_header {
	unsigned int	nod1_start;
	unsigned int	nod1_len;
	unsigned int	nod1_nod;
	unsigned int	nod1_data;

	unsigned int	nod2_start;
	unsigned int	nod2_len;
	unsigned int	nod2_nod;

	unsigned int	nod3_start;
	unsigned int	nod3_len;
	unsigned short	nod3_rec;
	unsigned int	nod3_nod;

	unsigned int	nod4_start;
	unsigned short	nod4_len;

	unsigned char	nod_data[1024];
	} nod_header;
public:
	nod_manager(std::string _main_file,unsigned int _file_offset,internal_file_type _file_type,unsigned char _xor_file,unsigned int _internal_size)
		: img_manager(_main_file,_file_offset,_file_type,_xor_file,_internal_size) {};
	
	virtual void	read_header();

	virtual void	set_data_start_offset(unsigned int _offset);
	virtual void	write_header();
};

#endif