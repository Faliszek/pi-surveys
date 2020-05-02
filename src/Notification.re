open Belt;
open NotificationContext;

let use = () => React.useContext(context);

type state = t;

type action = [ | `createMessage(messageType, string) | `destory(float)];

let reducer = (state, action: action) =>
  switch (action) {
  | `createMessage(type_, msg) => {
      ...state,
      notifications:
        state.notifications
        ->Array.concat([|
            {message: msg->React.string, id: Js.Date.now(), type_},
          |]),
    }

  | `destory(id) => {
      ...state,
      notifications: state.notifications->Array.keep(m => m.id !== id),
    }
  };

module Notification = {
  [@react.component]
  let make = (~message, ~time, ~onDestroy, ~type_) => {
    React.useEffect(() => {
      Js.Global.setTimeout(() => {onDestroy()}, time) |> ignore;

      None;
    });

    let color =
      TW.(
        switch (type_) {
        | `error => BackgroundColor(BgRed500)
        | `success => BackgroundColor(BgGreen500)
        }
      );

    let icon =
      switch (type_) {
      | `error => <Icons.XCircle />
      | `success => <Icons.CheckCircle />
      };

    <div
      onClick={_ => onDestroy()}
      className=TW.(
        [
          TextColor(TextWhite),
          color,
          Padding(P4),
          Width(W64),
          BorderRadius(Rounded),
          Margin(Mt10),
          BoxShadow(ShadowLg),
          Display(Flex),
          AlignItems(ItemsCenter),
        ]
        ->TW.make
      )>
      icon
      <span className=TW.([Margin(Ml2)]->TW.make)> message </span>
    </div>;
  };
};

module Provider = {
  [@react.component]
  let make = (~children) => {
    let (state, dispatch) = React.useReducer(reducer, initialState);

    <NotificationContext
      value={
        notifications: state.notifications,
        show: (type_, message) =>
          dispatch(`createMessage((type_, message))),
      }>
      children
      {switch (Webapi.Dom.(Document.querySelector("#messages", document))) {
       | Some(element) =>
         ReactDOMRe.createPortal(
           <div
             style={ReactDOMRe.Style.make(
               ~position="fixed",
               ~top="0",
               ~right="20px",
               ~zIndex="100",
               (),
             )}>
             {state.notifications
              ->Array.map(m =>
                  <Notification
                    type_={m.type_}
                    message={m.message}
                    time=2000
                    onDestroy={() => dispatch(`destory(m.id))}
                  />
                )
              ->React.array}
           </div>,
           element,
         )

       | None => React.null
       }}
    </NotificationContext>;
  };
};