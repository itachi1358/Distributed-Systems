/* add.x : RPC interface definition for adding two numbers */

struct numbers {
    int a;
    int b;
};

program ADD_PROG {
    version ADD_VERS {
        int ADD(numbers) = 1;
    } = 1;
} = 0x23451111;
