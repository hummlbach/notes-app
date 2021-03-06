/*
 * Copyright (C) 2012-2014 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.4
import Ubuntu.Components 1.3
import "../Theme"

AbstractButton {
    id: checkBox

    /*!
      Specifies whether the checkbox is checked or not. By default the property
      is set to false.
    */
    property bool isMultiSelect: true
    property bool checked: isMultiSelect ? root.selected : false
    width: implicitWidth
    // disable item mouse area to avoid conflicts with parent mouse area
    __mouseArea.enabled: isMultiSelect ? false : true

    /*!
      \internal
     */
    onTriggered: checked = !checked

    style: Theme.createStyleComponent(Qt.resolvedUrl("../Theme/CheckBoxStyle.qml"), checkBox)
}
