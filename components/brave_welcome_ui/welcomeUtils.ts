/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { Dispatch } from 'redux'
import { getSearchEngineProvidersSuccess } from './actions/welcome_actions'

export const getSearchEngineProviders = () => {
  return (dispatch: Dispatch) => {
    window.cr.sendWithPromise('getSearchEnginesList')
      .then((response: Welcome.SearchEngineListResponse) => {
        dispatch(getSearchEngineProvidersSuccess(response.defaults))
      })
      .catch((error: any) => {
        console.error('Could not load search providers', error)
      })
  }
}
