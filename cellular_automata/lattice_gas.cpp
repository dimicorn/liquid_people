#include "lattice_gas.hpp"

std::pair<UnitVector, int> LatticeGas::randomVelocity(const int &i, const int &j) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist8(1, 8), dist7(1, 7),
    dist6(1, 6), dist5(1, 5);
    int rnd8 = dist8(rng);
    int rnd7 = dist7(rng);
    int rnd6 = dist6(rng);
    int rnd5 = dist5(rng);
    // FIXME : scaling odd c_width and c_height
    // Top left node
    if (i == 0 && j == 0) {
        switch (rnd5 % 5) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(bottom_left, 1);
            case 2:
                return std::make_pair(bottom_right, 1);
            case 3:
                return std::make_pair(right, 1);
            case 4:
                return std::make_pair(zero, 1);
        }
    // Top right node
    } else if (i == c_height && j == 0) {
        switch (rnd5 % 5) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(left, 1);
            case 2:
                return std::make_pair(bottom_left, 1);
            case 3:
                return std::make_pair(bottom_right, 1);
            case 4:
                return std::make_pair(zero, 1);
        }
    // Rest of the top nodes
    } else if (j == 0) {
        switch (rnd6 % 6) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(left, 1);
            case 2:
                return std::make_pair(right, 1);
            case 3:
                return std::make_pair(bottom_left, 1);
            case 4:
                return std::make_pair(bottom_right, 1);
            case 5:
                return std::make_pair(zero, 1);
        }
    }

    // Bottom left node
    if (i == 0 && j == c_width) {
        switch (rnd5 % 5) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(top_left, 1);
            case 2:
                return std::make_pair(top_right, 1);
            case 3:
                return std::make_pair(right, 1);
            case 4:
                return std::make_pair(zero, 1);
        }
    // Bottom right node
    } else if ((j % 2 == 0 && i == c_height && j == c_width) ||
            (j % 2 == 1 && i == (c_height + 1) && j == c_width)) {
        switch (rnd5 % 5) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(left, 1);
            case 2:
                return std::make_pair(top_left, 1);
            case 3:
                return std::make_pair(top_right, 1);
            case 4:
                return std::make_pair(zero, 1);
        }
    // Rest of the bottom nodes
    } else if (j == c_width) {
        switch (rnd6 % 6) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(left, 1);
            case 2:
                return std::make_pair(right, 1);
            case 3:
                return std::make_pair(top_left, 1);
            case 4:
                return std::make_pair(top_right, 1);
            case 5:
                return std::make_pair(zero, 1);
        }
    }

    // Left even rows
    if (i == 0 && j % 2 == 0 && j != 0 && j != c_width) {
        switch (rnd7 % 7) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(top_left, 1);
            case 2:
                return std::make_pair(top_right, 1);
            case 3:
                return std::make_pair(right, 1);
            case 4:
                return std::make_pair(bottom_left, 1);
            case 5:
                return std::make_pair(bottom_right, 1);
            case 6:
                return std::make_pair(zero, 1);
        }
    // Left odd rows
    } else if (i == 0 && j % 2 == 1 && j != c_width) {
        switch (rnd5 % 5) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(top_right, 1);
            case 2:
                return std::make_pair(right, 1);
            case 3:
                return std::make_pair(bottom_right, 1);
            case 4:
                return std::make_pair(zero, 1);
        }
    }
    // Right even rows
    if (i == c_height && j % 2 == 0 && j != 0 && j != c_width) {
        switch (rnd7 % 7) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(top_left, 1);
            case 2:
                return std::make_pair(top_right, 1);
            case 3:
                return std::make_pair(left, 1);
            case 4:
                return std::make_pair(bottom_left, 1);
            case 5:
                return std::make_pair(bottom_right, 1);
            case 6:
                return std::make_pair(zero, 1);
        }
    // Right odd rows
    } else if (i == c_height + 1 && j % 2 == 1 && j != c_width) {
        switch (rnd5 % 5) {
            case 0:
                return std::make_pair(zero, 0);
            case 1:
                return std::make_pair(top_left, 1);
            case 2:
                return std::make_pair(left, 1);
            case 3:
                return std::make_pair(bottom_left, 1);
            case 4:
                return std::make_pair(zero, 1);
        }
    }

    // Internal nodes
    switch (rnd8 % 8) {
        case 0:
            return std::make_pair(zero, 0);
        case 1:
            return std::make_pair(left, 1);
        case 2:
            return std::make_pair(right, 1);
        case 3:
            return std::make_pair(top_left, 1);
        case 4:
            return std::make_pair(top_right, 1);
        case 5:
            return std::make_pair(bottom_left, 1);
        case 6:
            return std::make_pair(bottom_right, 1);
        case 7:
            return std::make_pair(zero, 1);
    }

    throw std::invalid_argument("No case found for velocity");
    exit(1);
}

void LatticeGas::initNodes(const int &N) {
    Node n;
    std::unordered_set<UnitVector, Hash> vels = {};
    UnitVector vel;
    int particleCount;
    bool isWall;

    for (int j = 0; j <= c_width; ++j) {
        /*
        if (j % 2 == 0) {
            for (int i = 0; i <= c_height; ++i) {
                isWall = false;
                particleCount = 0;
                vels = {zero};
                if (j == 4 || j == 8) {
                    std::pair<UnitVector, int> res = randomVelocity(i, j);
                    vel = res.first, particleCount = res.second;
                    vels = {vel};
                    if (particleCount != 0) {
                        // ++count;
                    }
                }
                if (i == 0 || i == c_height || j == 0 || j == c_width) {
                    isWall = true;
                }
                n = {vels, dl + i * cell_size, dl + j * sqrt3_2 * cell_size,
                    particleCount, isWall};
                nodes.push_back(n);
            }
        } else if (j % 2 == 1) {
            for (int i = 0; i <= c_height + 1; ++i) {
                isWall = false;
                particleCount = 0;
                vels = {zero};
                if (i == 0 || i == c_height || j == 0 || j == c_width) {
                    isWall = true;
                }
                n = {vels, dl + (i-0.5) * cell_size, dl + j * sqrt3_2 * cell_size,
                    particleCount, isWall};
                nodes.push_back(n);
            }
        }
        */
        if (j % 2 == 0) {
            for (int i = 0; i <= c_height; ++i) {
                isWall = false;
                std::pair<UnitVector, int> res = randomVelocity(i, j);
                vel = res.first, particleCount = res.second;
                if (particleCount != 0) {
                    vels = {vel};
                }
                if (i == 0 || i == c_height || j == 0 || j == c_width) {
                    isWall = true;
                }
                n = {vels, dl + i * cell_size, dl + j * sqrt3_2 * cell_size,
                    particleCount, isWall};
                nodes.push_back(n);
            }
        } else {
            for (int i = 0; i <= c_height + 1; ++i) {
                isWall = false;
                std::pair<UnitVector, int> res = randomVelocity(i, j);
                vel = res.first, particleCount = res.second;
                if (particleCount != 0) {
                    vels = {vel};
                }
                if (i == 0 || i == c_height + 1 || j == c_width) {
                    isWall = true;
                }
                n = {vels, dl + (i - 0.5) * cell_size, dl + j * sqrt3_2 * cell_size,
                    particleCount, isWall};
                nodes.push_back(n);
            }
        }
    }
}

void LatticeGas::updateNodes() {
    std::vector<Node> upd;
    for (int j = 0; j <= c_width; ++j) {
        if (j % 2 == 0) {
            for (int i = 0; i <= c_height; ++i) {
                upd.push_back(checkNeighbors(nodes[index(i, j)], i, j));
            }
        } else {
            for (int i = 0; i <= c_height + 1; ++i) {
                upd.push_back(checkNeighbors(nodes[index(i, j)], i, j));
            }
        }
    }
    nodes = upd;
    for (int j = 0; j <= c_width; ++j) {
        if (j % 2 == 0) {
            for (int i = 0; i <= c_height; ++i) {
                checkCollision(nodes[index(i, j)], i, j);
            }
        } else {
            for (int i = 0; i <= c_height + 1; ++i) {
                checkCollision(nodes[index(i, j)], i, j);
            }
        }
    }
}

bool LatticeGas::check_ind(const int &i, const int &j) {
    if (0 <= j && j <= c_width) {
        if (j % 2 == 0 && 0 <= i && i <= c_height) {
            return true;
        } else if (j % 2 == 1 && 0 <= i && i <= c_height + 1) {
            return true;
        }
    }
    return false;
}

Node LatticeGas::checkNeighbors(Node &n, const int &i, const int &j) {
    Node n_upd;
    n_upd.x = n.x;
    n_upd.y = n.y;
    n_upd.isWall = n.isWall;

    // zero velocity particle
    if (n.velocities.find(zero) != n.velocities.end() && n.particleCount == n.velocities.size()) {
        n_upd.velocities.insert(zero);
        ++n_upd.particleCount;
    }

    // fml
    // checking if left neighbor has right velocity
    if (check_ind(i-1, j) &&
    nodes[index(i-1, j)].velocities.find(right) != nodes[index(i-1, j)].velocities.end()) {
        n_upd.velocities.insert(right);
        ++n_upd.particleCount;
    }
    // right neighbor & left velocity
    if (check_ind(i+1, j) &&
    nodes[index(i+1, j)].velocities.find(left) != nodes[index(i+1, j)].velocities.end()) {
        n_upd.velocities.insert(left);
        ++n_upd.particleCount;
    }
        
    if (j % 2 == 0) {
        // top left neighbor & bottom right velocity
        if (check_ind(i, j-1) &&
        nodes[index(i, j-1)].velocities.find(bottom_right) !=
        nodes[index(i, j-1)].velocities.end()) {
            n_upd.velocities.insert(bottom_right);
            ++n_upd.particleCount;
        }
        // top right neighbor & bottom left velocity
        if (check_ind(i+1, j-1) &&
        nodes[index(i+1, j-1)].velocities.find(bottom_left) !=
        nodes[index(i+1, j-1)].velocities.end()) {
            n_upd.velocities.insert(bottom_left);
            ++n_upd.particleCount;
        }
        // bottom left neighbor & top right velocity
        if (check_ind(i, j+1) &&
        nodes[index(i, j+1)].velocities.find(top_right) !=
        nodes[index(i, j+1)].velocities.end()) {
            n_upd.velocities.insert(top_right);
            ++n_upd.particleCount;
        }
        // bottom right neighbor & top left velocity
        if (check_ind(i+1, j+1) &&
        nodes[index(i+1, j+1)].velocities.find(top_left) !=
        nodes[index(i+1, j+1)].velocities.end()) {
            n_upd.velocities.insert(top_left);
            ++n_upd.particleCount;
        }
    } else {
        // top left neighbor & bottom right velocity
        if (check_ind(i-1, j-1) &&
        nodes[index(i-1, j-1)].velocities.find(bottom_right) !=
        nodes[index(i-1, j-1)].velocities.end()) {
            n_upd.velocities.insert(bottom_right);
            ++n_upd.particleCount;
        }
        // top right neighbor & bottom left velocity
        if (check_ind(i, j-1) &&
        nodes[index(i, j-1)].velocities.find(bottom_left) !=
        nodes[index(i, j-1)].velocities.end()) {
            n_upd.velocities.insert(bottom_left);
            ++n_upd.particleCount;
        }
        // bottom left neighbor & top right velocity
        if (check_ind(i-1, j+1) &&
        nodes[index(i-1, j+1)].velocities.find(top_right) !=
        nodes[index(i-1, j+1)].velocities.end()) {
            n_upd.velocities.insert(top_right);
            ++n_upd.particleCount;
        }
        // bottom right neighbor & top left velocity
        if (check_ind(i, j+1) &&
        nodes[index(i, j+1)].velocities.find(top_left) !=
        nodes[index(i, j+1)].velocities.end()) {
            n_upd.velocities.insert(top_left);
            ++n_upd.particleCount;
        }
    }
    return n_upd;
}

void LatticeGas::checkCollision(Node &n, const int &i, const int &j) {
    // FIXME: Refactor this shit
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10);
    int rnd = dist(rng);

    /*
    // Particle collisions
    // Two particle head-on collision
    if (n.velocities.find(left) != n.velocities.end() &&
        n.velocities.find(right) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(right);
        if (rnd % 2 == 0) {
            v.value() = top_left;
            w.value() = bottom_right;
        } else {
            v.value() = bottom_left;
            w.value() = top_right;
        }
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(top_left) != n.velocities.end() && 
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(top_left);
        auto w = n.velocities.extract(bottom_right);
        if (rnd % 2 == 0) {
            v.value() = left;
            w.value() = right;
        } else {
            v.value() = top_right;
            w.value() = bottom_left;
        }
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(bottom_left) != n.velocities.end() && 
            n.velocities.find(top_right) != n.velocities.end()) {
        auto v = n.velocities.extract(bottom_left);
        auto w = n.velocities.extract(top_right);
        if (rnd % 2 == 0) {
            v.value() = left;
            w.value() = right;
        } else {
            v.value() = bottom_right;
            w.value() = top_left;
        }
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    }
    // Symmetric three particle collision
    if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(top_right) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(top_right);
        auto u = n.velocities.extract(bottom_right);
        v.value() = top_left;
        w.value() = right;
        u.value() = bottom_left;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
        n.velocities.insert(std::move(u));
    } else if (n.velocities.find(right) != n.velocities.end() &&
            n.velocities.find(top_left) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end()) {
        auto v = n.velocities.extract(right);
        auto w = n.velocities.extract(top_left);
        auto u = n.velocities.extract(bottom_left);
        v.value() = bottom_right;
        w.value() = top_right;
        u.value() = left;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
        n.velocities.insert(std::move(u));
    }
    // Four particle head-on collision
    if (n.velocities.find(top_left) != n.velocities.end() &&
            n.velocities.find(top_right) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(top_left);
        auto w = n.velocities.extract(top_right);
        auto u = n.velocities.extract(bottom_left);
        auto y = n.velocities.extract(bottom_right);
        if (rnd % 2 == 0) {
            v.value() = left;
            w.value() = top_left;
            u.value() = bottom_right;
            y.value() = right;
        } else {
            v.value() = top_right;
            w.value() = right;
            u.value()  = left;
            y.value() = bottom_left;
        }
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
        n.velocities.insert(std::move(u));
        n.velocities.insert(std::move(y));
    } else if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(right) != n.velocities.end() &&
            n.velocities.find(top_right) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(right);
        auto u = n.velocities.extract(top_right);
        auto y = n.velocities.extract(bottom_left);
        if (rnd % 2 == 0) {
            v.value() = bottom_left;
            w.value() = top_right;
            u.value() = top_left;
            y.value() = bottom_right;
        } else {
            v.value() = top_left;
            w.value() = bottom_right;
            u.value() = right;
            y.value() = left;
        }
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
        n.velocities.insert(std::move(u));
        n.velocities.insert(std::move(y));
    } else if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(right) != n.velocities.end() &&
            n.velocities.find(top_left) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(right);
        auto u = n.velocities.extract(top_left);
        auto y = n.velocities.extract(bottom_right);
        if (rnd % 2 == 0) {
            v.value() = top_left;
            w.value() = bottom_right;
            u.value() = top_right;
            y.value() = bottom_left;
        } else {
            v.value() = bottom_left;
            w.value() = top_right;
            u.value() = left;
            y.value() = right;
        }
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
        n.velocities.insert(std::move(u));
        n.velocities.insert(std::move(y));
    }
    // Two particle collision with spectator
    if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(right) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(right);
        v.value() = top_left;
        w.value() = bottom_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(top_left) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(top_left);
        auto w = n.velocities.extract(bottom_right);
        v.value() = left;
        w.value() = right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(top_right) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(top_right);
        auto w = n.velocities.extract(bottom_left);
        v.value() = right;
        w.value() = left;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(right) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(right);
        v.value() = bottom_left;
        w.value() = top_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(top_left) != n.velocities.end() &&
            n.velocities.find(top_right) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end()) {
        auto v = n.velocities.extract(top_left);
        auto w = n.velocities.extract(bottom_right);
        v.value() = left;
        w.value() = right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(right) != n.velocities.end() &&
            n.velocities.find(top_left) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(right);
        v.value() = bottom_left;
        w.value() = top_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(top_left) != n.velocities.end() &&
            n.velocities.find(top_right) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(top_left);
        auto w = n.velocities.extract(bottom_right);
        v.value() = left;
        w.value() = right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(right) != n.velocities.end() &&
            n.velocities.find(top_right) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(right);
        v.value() = top_left;
        w.value() = bottom_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    }
    // Rest particle collision
    if (n.velocities.find(zero) != n.velocities.end() &&
            n.velocities.find(left) != n.velocities.end()) {
        auto v = n.velocities.extract(zero);
        auto w = n.velocities.extract(left);
        v.value() = top_left;
        w.value() = bottom_left;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(top_left) != n.velocities.end() && 
            n.velocities.find(bottom_left) != n.velocities.end()) {
        auto v = n.velocities.extract(top_left);
        auto w = n.velocities.extract(bottom_left);
        v.value() = zero;
        w.value() = left;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(zero) != n.velocities.end() &&
            n.velocities.find(top_left) != n.velocities.end()) {
        auto v = n.velocities.extract(zero);
        auto w = n.velocities.extract(top_left);
        v.value() = left;
        w.value() = top_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(top_right) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(top_right);
        v.value() = zero;
        w.value() = top_left;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(zero) != n.velocities.end() &&
            n.velocities.find(top_right) != n.velocities.end()) {
        auto v = n.velocities.extract(zero);
        auto w = n.velocities.extract(top_right);
        v.value() = top_left;
        w.value() = right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(top_left) != n.velocities.end() &&
            n.velocities.find(right) != n.velocities.end()) {
        auto v = n.velocities.extract(top_left);
        auto w = n.velocities.extract(right);
        v.value() = zero;
        w.value() = top_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(zero) != n.velocities.end() &&
            n.velocities.find(right) != n.velocities.end()) {
        auto v = n.velocities.extract(zero);
        auto w = n.velocities.extract(right);
        v.value() = top_right;
        w.value() = bottom_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(top_right) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(top_right);
        auto w = n.velocities.extract(bottom_right);
        v.value() = zero;
        w.value() = right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(zero) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(zero);
        auto w = n.velocities.extract(bottom_right);
        v.value() = right;
        w.value() = bottom_left;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(right) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end()) {
        auto v = n.velocities.extract(right);
        auto w = n.velocities.extract(bottom_left);
        v.value() = zero;
        w.value() = bottom_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(zero) != n.velocities.end() &&
            n.velocities.find(bottom_left) != n.velocities.end()) {
        auto v = n.velocities.extract(zero);
        auto w = n.velocities.extract(bottom_left);
        v.value() = left;
        w.value() = bottom_right;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    } else if (n.velocities.find(left) != n.velocities.end() &&
            n.velocities.find(bottom_right) != n.velocities.end()) {
        auto v = n.velocities.extract(left);
        auto w = n.velocities.extract(bottom_right);
        v.value() = zero;
        w.value() = bottom_left;
        n.velocities.insert(std::move(v));
        n.velocities.insert(std::move(w));
    }
    */

    // Wall collision
    // Top left node
    if (i == 0 && j == 0) {
        if (n.velocities.find(left) != n.velocities.end()) {
            auto v = n.velocities.extract(left);
            v.value() = bottom_left;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(top_left) != n.velocities.end()) {
            auto v = n.velocities.extract(top_left);
            v.value() = (rnd % 2 == 0) ? bottom_left : right;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(top_right) != n.velocities.end()) {
            auto v = n.velocities.extract(top_right);
            v.value() = right;
            n.velocities.insert(std::move(v));
        }
    // Top right node
    } else if (i == c_height && j == 0) {
        if (n.velocities.find(right) != n.velocities.end()) {
            auto v = n.velocities.extract(right);
            v.value() = bottom_right;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(top_left) != n.velocities.end()) {
            auto v = n.velocities.extract(top_left);
            v.value() = left;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(top_right) != n.velocities.end()) {
            auto v = n.velocities.extract(top_right);
            v.value() = (rnd % 2 == 0) ? bottom_right : left;
            n.velocities.insert(std::move(v));
        }
    // Other top row nodes
    } else if (j == 0) {
        if (n.velocities.find(top_left) != n.velocities.end()) {
            auto v = n.velocities.extract(top_left);
            v.value() = bottom_left;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(top_right) != n.velocities.end()) {
            auto v = n.velocities.extract(top_right);
            v.value() = bottom_right;
            n.velocities.insert(std::move(v));
        }
    }

    // Bottom left node
    if (i == 0 && j == c_width) {
        if (n.velocities.find(left) != n.velocities.end()) {
            auto v = n.velocities.extract(left);
            v.value() = top_left;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(bottom_left) != n.velocities.end()) {
            auto v = n.velocities.extract(bottom_left);
            v.value() = (rnd % 2 == 0) ? top_left : right;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(bottom_right) != n.velocities.end()) {
            auto v = n.velocities.extract(bottom_right);
            v.value() = right;
            n.velocities.insert(std::move(v));
    }
    // Bottom right node
    } else if ((j % 2 == 0 && i == c_height && j == c_width) ||
            (j % 2 == 1 && i == c_height + 1 && j == c_width)) {
        if (n.velocities.find(right) != n.velocities.end()) {
            auto v = n.velocities.extract(right);
            v.value() = top_right;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(bottom_left) != n.velocities.end()) {
            auto v = n.velocities.extract(bottom_left);
            v.value() = left;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(bottom_right) != n.velocities.end()) {
            auto v = n.velocities.extract(bottom_right);
            v.value() = (rnd % 2 == 0) ? top_right : left;
            n.velocities.insert(std::move(v));
        }
    // Other bottom nodes
    } else if (j == c_width) {
        if (n.velocities.find(bottom_left) != n.velocities.end()) {
            auto v = n.velocities.extract(bottom_left);
            v.value() = top_left;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(bottom_right) != n.velocities.end()) {
            auto v = n.velocities.extract(bottom_right);
            v.value() = top_right;
            n.velocities.insert(std::move(v));
        }
    }
     
    // Left even rows
    if (i == 0 && j % 2 == 0 && j != 0 && j != c_width) {
        if (n.velocities.find(left) != n.velocities.end()) {
            auto v = n.velocities.extract(left);
            v.value() = (rnd % 2 == 0) ? top_left : bottom_left;
            n.velocities.insert(std::move(v));
        }
    // Left odd rows
    } else if (i == 0 && j % 2 == 1 && j != c_width) {
        if (n.velocities.find(left) != n.velocities.end()) {
            auto v = n.velocities.extract(left);
            v.value() = (rnd % 2 == 0) ? top_right : bottom_right;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(top_left) != n.velocities.end()) {
            auto v = n.velocities.extract(top_left);
            v.value() = top_right;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(bottom_left) != n.velocities.end()) {
            auto v = n.velocities.extract(bottom_left);
            v.value() = bottom_right;
            n.velocities.insert(std::move(v));
        }
    }

    // Right even rows
    if (i == c_height && j % 2 == 0 && j != 0 && j != c_width) {
        if (n.velocities.find(right) != n.velocities.end()) {
            auto v = n.velocities.extract(right);
            v.value() = (rnd % 2 == 0) ? top_right : bottom_right;
            n.velocities.insert(std::move(v));
        }
    }
    // Right odd rows
    else if (i == (c_height + 1) && j % 2 == 1 && j != c_width) {
        if (n.velocities.find(right) != n.velocities.end()) {
            auto v = n.velocities.extract(right);
            v.value() = (rnd % 2 == 0) ? top_left : bottom_left;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(top_right) != n.velocities.end()) {
            auto v = n.velocities.extract(top_right);
            v.value() = top_left;
            n.velocities.insert(std::move(v));
        }
        if (n.velocities.find(bottom_right) != n.velocities.end()) {
            auto v = n.velocities.extract(bottom_right);
            v.value() = bottom_left;
            n.velocities.insert(std::move(v));
        }
    }
}

void LatticeGas::drawNode(const Node &n) {
   if (n.particleCount == 0) {
       return;
   }
   std::unordered_set<UnitVector, Hash> vels = n.velocities;
   for (const auto &vel : vels) {
       if (vel == zero) {
           double radius = cell_size / 16;
           sf::CircleShape node(radius);
           node.setPosition(n.x - radius, n.y - radius);
           node.setFillColor(sf::Color::White);
           window.draw(node);        
       } else {
           sf::Vector2f start = sf::Vector2f(n.x, n.y);
           sf::Vector2f end;
       
           if (vel == left) {
                end = sf::Vector2f(n.x + 0.5 * left.x * cell_size, n.y + 0.5 * left.y * cell_size);
           } else if (vel == right) {
                end = sf::Vector2f(n.x + 0.5 * right.x * cell_size, n.y + 0.5 * right.y * cell_size);
           } else if (vel == top_left) {
                end = sf::Vector2f(n.x + 0.5 * top_left.x * cell_size,
                        n.y + 0.5 * top_left.y * cell_size);
           } else if (vel == top_right) {
                end = sf::Vector2f(n.x + 0.5 * top_right.x * cell_size,
                        n.y + 0.5 * top_right.y * cell_size);
           } else if (vel == bottom_left) {
                end = sf::Vector2f(n.x + 0.5 * bottom_left.x * cell_size,
                        n.y + 0.5 * bottom_left.y * cell_size);
           } else if (vel == bottom_right) {
                end = sf::Vector2f(n.x + 0.5 * bottom_right.x * cell_size,
                        n.y + 0.5 * bottom_right.y * cell_size);
           }

            sf::Vertex node[] = {
                sf::Vertex(start, sf::Color::White),
                sf::Vertex(end, sf::Color::White)
            };
            window.draw(node, 2, sf::Lines);
       }
   }
}

void LatticeGas::drawTriangle(const int &i, const int &j) {
    sf::Vertex left[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size),
        sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (i%2) + j) * sqrt3 * cell_size), sf::Color::Red)
    };
    sf::Vertex right[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (i%2) + j) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red)
    };
    sf::Vertex bottom[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size),
        sf::Color::Red),
    };

    window.draw(left, 2, sf::Lines);
    window.draw(right, 2, sf::Lines);
    window.draw(bottom, 2, sf::Lines);
}

void LatticeGas::drawRTriangle(const int &i, const int &j) {
    sf::Vertex left[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (-i%2) + j + 1) * sqrt3 * cell_size), sf::Color::Red)
    };
    sf::Vertex right[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (-i%2) + j + 1) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red)
    };
    sf::Vertex top[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red),
    };

    window.draw(top, 2, sf::Lines);
    window.draw(left, 2, sf::Lines);
    window.draw(right, 2, sf::Lines);
}
