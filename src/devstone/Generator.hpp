/**
 * @file Generator.hpp
 * @author The DEVSTONE Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * DEVSTONE - a DEVS model generator
 * This file is a part of the DEVSTONE software
 *
 * Copyright (C) 2014 ULCO http://www.univ-litoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEVSTONE_GENERATOR
#define DEVSTONE_GENERATOR 1

#include <devstone/TreeNode.hpp>

namespace devstone {

    enum GeneratorType {
        LI = 0, HI, HO
    };

    class Generator
    {
    public:
        Generator(GeneratorType type, int depth, int width, double itt,
                  double ett) : _type(type), _depth(depth), _width(width),
                                _itt(itt), _ett(ett)
        { }

        TreeNode* generate() const;

    private:
        Graph* build_graph_LI() const;
        Graph* build_low_level_graph() const;
        TreeNode* generate_LI() const;
        TreeNode* generate_HI() const;
        TreeNode* generate_HO() const;

        GeneratorType _type;
        int _depth;
        int _width;
        double _itt;
        double _ett;
    };

} // namespace devstone

#endif
