/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2013-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#ifndef UTILS_VARIANT_H
#define UTILS_VARIANT_H

#include "DllMacro.h"

#include <QString>
#include <QVariantMap>

namespace CalamaresUtils
{
/**
 * Get a bool value from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT bool getBool( const QVariantMap& map, const QString& key, bool d = false );

/**
 * Get a string value from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT QString getString( const QVariantMap& map, const QString& key, const QString& d = QString() );

/**
 * Get a string list from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT QStringList getStringList( const QVariantMap& map, const QString& key, const QStringList& d = QStringList() );

/**
 * Get an integer value from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT qint64 getInteger( const QVariantMap& map, const QString& key, qint64 d = 0);

/**
 * Get an unsigned integer value from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT quint64 getUnsignedInteger( const QVariantMap& map, const QString& key, quint64 d = 0 );

/**
 * Get a double value from a mapping with a given key (integers are converted); returns @p d if no value.
 */
DLLEXPORT double getDouble( const QVariantMap& map, const QString& key, double d = 0.0 );

/**
 * Returns a sub-map (i.e. a nested map) from a given mapping with a 
 * given key. @p success is set to true if the @p key exists
 * in @p map and converts to a map, false otherwise.
 *
 * Returns @p d if there is no such key or it is not a map-value.
 * (e.g. if @p success is false).
 */
DLLEXPORT QVariantMap getSubMap( const QVariantMap& map, const QString& key, bool& success, const QVariantMap& d = QVariantMap() );
}  // namespace CalamaresUtils

#endif
