struct at24_prv {
        struct i2c_client client_prv;
        struct kobject *at24_kobj;
        char *ptr;
        unsigned int size;
        unsigned int pagesize;
        unsigned int address_width;
        unsigned int page_no;
};

