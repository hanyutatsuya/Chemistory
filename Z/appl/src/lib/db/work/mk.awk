{
	printf ( "$(SRC_DB_DIR)/%s.o	:	$(SRC_DB_DIR)/%s.c  $(INCS_DB)\n", $1, $1 ) ;
    printf ( "\t$(CC) $(CFLAGS) -c $(SRC_DB_DIR)/%s.c $(FLG_INC) -o $(SRC_DB_DIR)/%s.o\n\n", $1, $1 ) ;
}
