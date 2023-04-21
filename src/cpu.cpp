#include <algorithm>
#include <sstream>
#include <iomanip>
#include "cpu.h"

std::shared_ptr<cpu> cpu::instance = nullptr;

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
    distribution = std::uniform_int_distribution<uint8_t>(0, 255);

    std::cout << "CHIP-8 Core initialized." << std::endl;
}

cpu::~cpu() {
    std::cout << "CHIP-8 Core destroyed." << std::endl;
}

void cpu::fetch() {
    opcode = memory[pc] << 8 | memory[pc + 1];
}

void cpu::execute() {
    switch (xh(opcode)) {
        case 0x0:
            switch (kk(opcode)) {
                default:
                    illegal();
                    break;
                case 0xE0:
                    clear_display();
                    break;
                case 0xEE:
                    ret();
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
                    v[0xF] = (v[xl(opcode)] + v[yh(opcode)] > 0xFF) ? 1 : 0;
                    v[xl(opcode)] += v[yh(opcode)];
                    break;
                case 0x5:
                    v[0xF] = (v[xl(opcode)] > v[yh(opcode)]) ? 1 : 0;
                    v[xl(opcode)] -= v[yh(opcode)];
                    break;
                case 0x6:
                    v[0xF] = v[xl(opcode)] & 0x1;
                    v[xl(opcode)] >>= 1;
                    break;
                case 0x7:
                    v[0xF] = (v[yh(opcode)] > v[xl(opcode)]) ? 1 : 0;
                    v[xl(opcode)] = v[yh(opcode)] - v[xl(opcode)];
                    break;
                case 0xE:
                    v[0xF] = v[xl(opcode)] >> 7;
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
        default:
            illegal();
            break;
    }
}

void cpu::gen_random() {
    v[xl(opcode)] = distribution(generator) && kk(opcode);
}

void cpu::cycle() {
    if (pc > info::MEMORY_SIZE) {
        std::cerr << "Program counter out of bounds. Exiting..." << std::endl;
        exit(-1);
    }
    draw_flag = false;
    fetch();
    pc += 2;
    if (debug) {
        log();
    }
    execute();
}

void cpu::update_timers() {
    if (dt > 0) {
        dt--;
    }
    if (st > 0) {
        sound.play();
        st--;
    } else {
        sound.stop();
    }
}

void cpu::clear_display() {
    display.fill(info::P_OFF);
}

void cpu::ret() {
    pc = stack[--sp];
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
    auto x = v[xl(opcode)];
    auto y = v[yh(opcode)];
    auto height = yl(opcode);
    for (int row = 0; row < height; row++) {
        auto line = memory[index + row];
        for (int col = 0; col < 8; col++) {
            if (line & (0x80 >> col)) {
                uint32_t pixel_index = (y + row) % info::SCREEN_HEIGHT * info::SCREEN_WIDTH + (x + col) % info::SCREEN_WIDTH;
                if (display[pixel_index] == info::P_ON) {
                    v[0xF] = 1;
                }
                display[pixel_index] ^= info::P_ON;
            }
        }
    }
    draw_flag = true;
}

void cpu::illegal() {
    std::cerr << "ERROR: " << std::hex << std::setw(4) << std::setfill('0') << opcode
              << " - No such opcode exists. Exiting..." << std::dec << std::endl;
    dump_memory();
    exit(-1);
}

void cpu::log() {
    std::ostringstream oss;
    std::for_each(stack.begin(), stack.end(), [&oss](uint16_t elem) {
        oss << std::hex << elem << ", ";
    });
    std::string stack_str = oss.str();
    stack_str.pop_back();
    stack_str.pop_back();
    std::cout << "PC: " << std::hex << std::setw(4) << std::setfill('0') << pc
              << ", OP: " << std::hex << std::setw(4) << std::setfill('0') << opcode
              << ", I: " << std::hex << std::setw(4) << std::setfill('0') << index
              << " Stack: " << stack_str << std::endl;
}

void cpu::set_sound(const audio &src) {
    cpu::sound = src;
}

std::shared_ptr<cpu> cpu::getInstance() {
    if (instance == nullptr) {
        instance = std::shared_ptr<cpu>(new cpu());
    }
    return instance;
}

void cpu::load_rom(const std::shared_ptr<rom> &rom) {
    auto data = rom->get_data();
    for (int j = 0; j < rom->get_size(); j++) {
        memory[info::PC_START + j] = data[j];
    }
}

void cpu::dump_memory() {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (int i = 0; i < info::MEMORY_SIZE; i += 16) {
        oss << std::setw(4) << i << ": ";
        for (int j = 0; j < 16; j++) {
            oss << std::setw(2) << static_cast<int>(memory[i + j]) << " ";
        }
        oss << "\n";
    }
    std::cout << oss.str() << std::endl;
}

