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

#include "Config.h"

#include "modulesystem/ModuleManager.h"
#include "network/Manager.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

Config::Config( QObject* parent )
    : QObject( parent )
{
}

Config::~Config() {}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    QString region = CalamaresUtils::getString( configurationMap, "region" );
    QString zone = CalamaresUtils::getString( configurationMap, "zone" );
    if ( !region.isEmpty() && !zone.isEmpty() )
    {
        m_startingTimezone = CalamaresUtils::GeoIP::RegionZonePair( region, zone );
    }
    else
    {
        m_startingTimezone
            = CalamaresUtils::GeoIP::RegionZonePair( QStringLiteral( "America" ), QStringLiteral( "New_York" ) );
    }
    m_currentTimezone = m_startingTimezone;
    emit currentRegionChanged();
    emit currentZoneChanged();

    bool ok = false;
    QVariantMap geoip = CalamaresUtils::getSubMap( configurationMap, "geoip", ok );
    if ( ok )
    {
        QString url = CalamaresUtils::getString( geoip, "url" );
        QString style = CalamaresUtils::getString( geoip, "style" );
        QString selector = CalamaresUtils::getString( geoip, "selector" );

        m_geoip = std::make_unique< CalamaresUtils::GeoIP::Handler >( style, url, selector );
        if ( !m_geoip->isValid() )
        {
            cWarning() << "GeoIP Style" << style << "is not recognized.";
        }
    }
}

void
Config::doGeoIPLookup()
{
    if ( m_geoip && m_geoip->isValid() )
    {
        auto& network = CalamaresUtils::Network::Manager::instance();
        if ( network.hasInternet() || network.synchronousPing( m_geoip->url() ) )
        {
            m_currentTimezone = m_geoip->get();
            if ( !m_currentTimezone.isValid() )
            {
                cWarning() << "GeoIP lookup at" << m_geoip->url() << "failed.";
                m_currentTimezone = m_startingTimezone;
            }
            else
            {
                // We assume GeoIP happens just once, at startup, and that
                // that is then the starting location for this run.
                m_startingTimezone = m_currentTimezone;
            }
            emit currentRegionChanged();
            emit currentZoneChanged();
        }
    }
}
