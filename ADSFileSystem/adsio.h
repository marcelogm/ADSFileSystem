typedef struct  {
	int coisa;
} ADS_FILE;

ADS_FILE* ADS_open( const char * filename);

size_t ADS_write( const void * ptr, size_t size, size_t count, FILE * stream );

size_t ADS_read ( void * ptr, size_t size, size_t count, FILE * stream );

int ADS_close( FILE * stream );
