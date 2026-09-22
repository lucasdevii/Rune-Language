int Hash(const char *identifier){
    unsigned long hash = 0;

    while(*identifier){
        hash = hash * 31 + (unsigned char)*identifier;
        identifier++;
    }

    return hash % 50;
}