type token = option(string);
type t = {
  token,
  setToken: token => unit,
};

let initialState = {token: None, setToken: _ => ()};

/** ContextProvider.re */
let context = React.createContext(initialState);

let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};

let make = React.Context.provider(context);