extern unsigned int  vectors_start, vectors_end;
extern unsigned char _bss_start, _bss_end;

void copy_vectors(void)
{
	unsigned int * vect_src = &vectors_start;
	unsigned int * vect_dest = (unsigned int *)0;
	while(vect_src != (&vectors_end))
	{
		*vect_dest = *vect_src;
		vect_dest++;
		vect_src++;
	}
}

void init_sections(void)
{
	unsigned char * bss_start = &_bss_start;
	unsigned char * bss_end = &_bss_end;
	while(bss_start != bss_end)
		*bss_start++ = 0;
}
