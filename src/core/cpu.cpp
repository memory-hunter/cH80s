#include "cpu.h"

cpu *cpu::instance = nullptr;

cpu::cpu() = default;

cpu *cpu::getInstance() {
    if (instance == nullptr) {
        instance = new cpu();
    }
    return instance;
}

void cpu::init() {
    pc = constants::PC_START;
    opcode = 0x0000;
    index = 0;
    sp = 0;
    dt = 0;
    st = 0;

    memset(display, constants::P_OFF, sizeof(display));
    memset(stack, 0, sizeof(stack));
    memset(v, 0, sizeof(v));
    memset(memory, 0, sizeof(memory));

    for (int j = 0; j < 80; j++) {
        memory[j] = font_set[j];
    }

    std::cout << "CHIP-8 Core initialized" << std::endl;
}

void cpu::fetch() {
    opcode = memory[pc] << 8 | memory[pc + 1];
}

void cpu::execute() {
    switch (xh(opcode)) {
        default:
            illegal();
            break;
        case 0x0:
            switch (yl(opcode)) {
                case 0x0:
                    clear_display();
                    break;
                case 0xE:
                    ret();
                    break;
                default:
                    illegal();
                    break;
            }
            break;
        case 0x1:
            jump();
            break;
        case 0x2:
            call();
            break;
        case 0x3:
            if (v[xl(opcode)] == kk(opcode)) {
                skip();
            }
            break;
        case 0x4:
            if (v[xl(opcode)] != kk(opcode)) {
                skip();
            }
            break;
        case 0x5:
            if (v[xl(opcode)] == v[yh(opcode)]) {
                skip();
            }
            break;
        case 0x6:
            v[xl(opcode)] = kk(opcode);
            break;
        case 0x7:
            v[xl(opcode)] += kk(opcode);
            break;
        case 0x8:
            switch (yl(opcode)) {
                case 0x0:
                    v[xl(opcode)] = v[yh(opcode)];
                    break;
                case 0x1:
                    v[xl(opcode)] |= v[yh(opcode)];
                    break;
                case 0x2:
                    v[xl(opcode)] &= v[yh(opcode)];
                    break;
                case 0x3:
                    v[xl(opcode)] ^= v[yh(opcode)];
                    break;
                case 0x4:
                    v[xl(opcode)] += v[yh(opcode)];
                    break;
                case 0x5:
                    v[xl(opcode)] -= v[yh(opcode)];
                    break;
                case 0x6:
                    v[xl(opcode)] >>= 1;
                    break;
                case 0x7:
                    v[xl(opcode)] = v[yh(opcode)] - v[xl(opcode)];
                    break;
                case 0xE:
                    v[xl(opcode)] <<= 1;
                    break;
                default:
                    illegal();
                    break;
            }
            break;
        case 0x9:
            if (v[xl(opcode)] != v[yh(opcode)]) {
                skip();
            }
            break;
        case 0xA:
            index = nnn(opcode);
            break;
        case 0xB:
            pc = v[0] + nnn(opcode);
            break;
        case 0xC:
            gen_random();
            break;
        case 0xD:
            draw();
            break;
        case 0xE:
            switch (kk(opcode)) {
                case 0x9E:
                    if (keys[v[xl(opcode)]]) {
                        skip();
                    }
                    break;
                case 0xA1:
                    if (!keys[v[xl(opcode)]]) {
                        skip();
                    }
                    break;
                default:
                    illegal();
                    break;
            }
            break;
        case 0xF:
            switch (kk(opcode)) {
                case 0x07:
                    v[xl(opcode)] = dt;
                    break;
                case 0x0A:
                    for (int j = 0; j < 16; j++) {
                        if (keys[j]) {
                            v[xl(opcode)] = j;
                            break;
                        } else if (j == 15) {
                            pc -= 2;
                        }
                    }
                    break;
                case 0x15:
                    dt = v[xl(opcode)];
                    break;
                case 0x18:
                    st = v[xl(opcode)];
                    break;
                case 0x1E:
                    index + v[xl(opcode)] > 0xFFF ? v[0xF] = 1 : v[0xF] = 0;
                    index += v[xl(opcode)];
                    index &= 0xFFF;
                    break;
                case 0x29:
                    index = v[xl(opcode)] * 5;
                    index &= 0xFFF;
                    break;
                case 0x33:
                    memory[index] = v[xl(opcode)] / 100;
                    memory[index + 1] = (v[xl(opcode)] / 10) % 10;
                    memory[index + 2] = (v[xl(opcode)] % 100) % 10;
                    break;
                case 0x55:
                    for (int j = 0; j < xl(opcode); j++) {
                        memory[index + j] = v[j];
                    }
                    break;
                case 0x65:
                    for (int j = 0; j < xl(opcode); j++) {
                        v[j] = memory[index + j];
                    }
                    break;
                default:
                    illegal();
                    break;
            }
            break;
    }
}

void cpu::gen_random() {
    static auto generator = std::default_random_engine(std::random_device()());
    static auto distribution = std::uniform_int_distribution<int>(0, 255);
    v[xl(opcode)] = distribution(generator);
}

void cpu::cycle() {
    std::cout << std::hex << "PC: " << pc << " OP: " << opcode << " I: " << index << " SP: " << stack[sp] << std::endl;
    fetch();
    pc += 2;
    execute();
    update_timers();
}

void cpu::update_timers() {
    if (dt > 0) {
        dt--;
    }
    if (st > 0) {
        st--;
    }
}

void cpu::clear_display() {
    memset(display, constants::P_OFF, sizeof(display));
}

void cpu::ret() {
    pc = stack[--sp];
    stack[sp+1] = 0;
    std::cout << std::hex << "PC: " << pc << std::endl;
}

void cpu::call() {
    stack[sp++] = pc;
    jump();
}

void cpu::skip() {
    pc += 2;
}

void cpu::jump() {
    pc = nnn(opcode);
}

void cpu::draw() {
    int x = v[xl(opcode)];
    int y = v[yh(opcode)];
    int height = yl(opcode);
    int pixel;
    for (int j = 0; j < height; j++) {
        pixel = memory[index + j];
        for (int k = 0; k < 8; k++) {
            if (pixel & (0x80 >> k)) {
                if (display[(x + k) + (y + j) * constants::SCREEN_WIDTH]) {
                    v[0xF] = 1;
                }
                display[(x + k) + (y + j) * constants::SCREEN_WIDTH] ^= constants::P_ON;
            }
        }
    }
}

void cpu::illegal() const {
    std::cerr << "ERROR: " << std::hex << opcode << " - No such opcode exists. Terminating." << std::endl;
    exit(-1);
}

void cpu::load_rom(rom &rom) {
    for (int j = 0; j < rom.getSize(); j++) {
        memory[constants::PC_START + j] = rom.getData()[j];
    }
}
