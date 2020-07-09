/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
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
 */

#ifndef LOCALE_CONFIG_H
#define LOCALE_CONFIG_H

#include "geoip/Handler.h"

#include <QObject>

class Config : public QObject
{
    Q_OBJECT

    /// @brief Current region (America, Asia, ..) for the timezone
    Q_PROPERTY( QString currentRegion READ currentRegion NOTIFY currentRegionChanged )
    /// @brief Current zone (Amsterdam, Karachi, Kentucky/Monticello)
    Q_PROPERTY( QString currentZone READ currentZone NOTIFY currentZoneChanged )

public:
    Config( QObject* parent = nullptr );
    ~Config() override;

    void setConfigurationMap( const QVariantMap& );

    /** @brief synchronous GeoIP lookup
     *
     * Because this is synchronous, call it from somewhere other than
     * the UI thread. It is recommended to do this in checkRequirements()
     * of the view step, because that is a threaded, synchronous-friendly,
     * part of the startup of Calamares.
     */
    void doGeoIPLookup();

public Q_SLOTS:
    QString currentRegion() const { return m_currentTimezone.first; }
    QString currentZone() const { return m_currentTimezone.second; }

signals:
    void currentRegionChanged();
    void currentZoneChanged();
    void currentLocationChanged( CalamaresUtils::GeoIP::RegionZonePair );

private:
    std::unique_ptr< CalamaresUtils::GeoIP::Handler > m_geoip;
    CalamaresUtils::GeoIP::RegionZonePair m_startingTimezone;
    CalamaresUtils::GeoIP::RegionZonePair m_currentTimezone;
};


#endif
