#include "cpu.h"

cpu *cpu::instance = nullptr;

cpu::cpu() {
    pc = info::PC_START;
    opcode = index = sp = dt = st = 0;
    draw_flag = false;

    display.fill(info::P_OFF);
    stack.fill(0);
    v.fill(0);
    memory.fill(0);

    std::copy(font_set.begin(), font_set.end(), memory.begin());

    generator = std::default_random_engine(std::random_device()());
    distribution = std::uniform_int_distribution<int>(0, 255);

    std::cout << "CHIP-8 Core initialized." << std::endl;
}

cpu::~cpu() {
    std::cout << "CHIP-8 Core destroyed." << std::endl;
}

cpu *cpu::getInstance() {
    if (instance == nullptr) {
        instance = new cpu();
    }
    return instance;
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
                    if (v[yh(opcode)] > v[xl(opcode)]) {
                        v[0xF] = 0;
                    } else {
                        v[0xF] = 1;
                    }
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
                    for (int j = 0; j <= xl(opcode); j++) {
                        memory[index + j] = v[j];
                    }
                    (index += (xl(opcode)))++;
                    break;
                case 0x65:
                    for (int j = 0; j <= xl(opcode); j++) {
                        v[j] = memory[index + j];
                    }
                    (index += (xl(opcode)))++;
                    break;
                default:
                    illegal();
                    break;
            }
            break;
    }
}

void cpu::gen_random() {
    v[xl(opcode)] = distribution(generator) && kk(opcode);
}

void cpu::cycle() {
    if (debug) {
        log();
    }
    draw_flag = false;
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
    display.fill(info::P_OFF);
}

void cpu::ret() {
    pc = stack[--sp];
    stack[sp + 1] = 0;
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
    v[0xF] = 0;
    int x = v[xl(opcode)];
    int y = v[yh(opcode)];
    int height = yl(opcode) % 16;
    for (int j = 0; j < height; j++) {
        int line = memory[index + j];
        for (int k = 0; k < 8; k++) {
            int pixel = (line & (0x80 >> k));
            if (pixel) {
                if (display[((y + j) * info::SCREEN_WIDTH) + (x + k) % 2048] == info::P_ON) {
                    v[0xF] = 1;
                }
                display[(y + j) * info::SCREEN_WIDTH + (x + k) % 2048] ^= info::P_ON;
            }
        }
    }
    draw_flag = true;
}

void cpu::illegal() const {
    std::cerr << "ERROR: " << std::hex << opcode << " - No such opcode exists. Terminating." << std::dec << std::endl;
    exit(-1);
}

void cpu::load_rom(rom *rom) {
    for (int j = 0; j < rom->get_size(); j++) {
        memory[info::PC_START + j] = rom->get_data()[j];
    }
    std::copy(memory.begin() + info::PC_START, memory.begin() + info::PC_START + rom->get_size(), rom->get_data().begin());
}

void cpu::log() {
    std::cout << std::hex << "PC: " << pc << " OP: " << opcode << " I: " << index << " SP: " << stack[sp] << std::endl;
}
